# GPU 数据传输示例

## 概述

本示例深入演示了 Coin3D 如何将几何数据传输到 GPU，以及不同的数据组织方式对性能的影响。

## 主要演示内容

### 1. 顶点数据组织方式对比

#### SoFaceSet（无索引）
- 每个面独立存储所有顶点
- 顶点数据存在大量重复
- 适合简单场景或顶点很少重用的情况

**示例：立方体**
```
顶点数: 24 个（6个面 × 4个顶点/面）
内存使用: 24 × 3 × 4 bytes = 288 bytes
问题: 8个唯一顶点被重复存储3次
```

#### SoIndexedFaceSet（使用索引）
- 顶点只存储一次，通过索引引用
- 大幅减少内存使用和数据传输量
- GPU 可以重用顶点数据（顶点缓存优化）

**示例：立方体**
```
顶点数: 8 个（唯一顶点）
索引数: 30 个（包括面结束标记）
内存使用: 8 × 3 × 4 + 30 × 4 = 216 bytes
节省: 约 25% 内存
```

### 2. 复杂网格性能对比

示例创建了两个 50×50 的细分网格：

**不使用索引（SoFaceSet）**
```
顶点数: 2,500 × 4 = 10,000 个（大量重复）
内存: 10,000 × 3 × 4 bytes = 120 KB
传输到GPU: 每帧需要传输全部数据
```

**使用索引（SoIndexedFaceSet）**
```
顶点数: 51 × 51 = 2,601 个（无重复）
索引数: 约 12,500 个
内存: 2,601 × 3 × 4 + 12,500 × 4 = 81 KB
节省: 约 32% 内存
GPU缓存: 顶点重用率高，缓存效率好
```

## GPU 数据传输流程

### 传统方式（立即模式）

```cpp
// Coin3D 内部（简化）
void SoFaceSet::GLRender(SoGLRenderAction* action)
{
    const SoCoordinateElement* coords = 
        SoCoordinateElement::getInstance(state);
    
    glBegin(GL_QUADS);
    for (each face) {
        for (each vertex in face) {
            SbVec3f point = coords->get3(vertexIndex);
            glVertex3fv(point.getValue());  // 传输到GPU
        }
    }
    glEnd();
}
```

**特点**：
- 每帧都要重新传输所有顶点数据
- CPU到GPU的总线带宽消耗大
- 现代OpenGL已废弃此方式

### 现代方式（VBO）

```cpp
// Coin3D 内部使用 VBO（简化）
void SoIndexedFaceSet::GLRender(SoGLRenderAction* action)
{
    // 1. 首次渲染时创建VBO
    if (!vboCreated) {
        glGenBuffers(1, &vertexVBO);
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glBufferData(GL_ARRAY_BUFFER, 
                     vertexCount * sizeof(SbVec3f),
                     vertexData,
                     GL_STATIC_DRAW);  // 上传到GPU显存
        
        glGenBuffers(1, &indexVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indexCount * sizeof(int32_t),
                     indexData,
                     GL_STATIC_DRAW);  // 上传索引到GPU
        
        vboCreated = true;
    }
    
    // 2. 后续帧直接使用GPU中的数据
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glDrawElements(GL_QUADS, indexCount, GL_UNSIGNED_INT, 0);
    
    // 无需重新传输数据！
}
```

**优势**：
- 数据存储在GPU显存中
- 只在首次渲染时传输一次
- 后续帧直接使用GPU中的数据
- 大幅减少CPU-GPU数据传输

## 性能优势总结

### 内存优势

| 方式 | 立方体 | 50×50网格 |
|------|--------|-----------|
| FaceSet | 288 bytes | ~120 KB |
| IndexedFaceSet | 216 bytes | ~81 KB |
| 节省 | 25% | 32% |

### GPU效率优势

**顶点缓存重用**：
- 现代GPU有顶点缓存（Post-T&L Cache）
- IndexedFaceSet允许GPU重用已处理的顶点
- 减少顶点着色器的执行次数

**示例**：
```
FaceSet:      10,000 顶点 → 10,000 次顶点着色器执行
IndexedFaceSet: 2,601 顶点 →  2,601 次顶点着色器执行
减少: 约 74% 的顶点处理工作量
```

## 运行示例

### 编译

```bash
mkdir build
cd build
cmake .. -DBUILD_COIN3D_EXAMPLES=ON
make gpu_data_transfer_example
```

### 运行

```bash
./coin3d_examples/gpu_data_transfer/gpu_data_transfer_example
```

### 预期输出

控制台将显示：
- 每种数据组织方式的详细内存使用统计
- 顶点数和索引数的对比
- 内存节省百分比

窗口将显示：
- 左上：FaceSet 立方体（红色）
- 右上：IndexedFaceSet 立方体（绿色）
- 左下：FaceSet 网格（紫色）
- 右下：IndexedFaceSet 网格（青色）

### 性能观察

旋转视图时，您可能会注意到：
- 右侧的对象（使用索引）渲染更流畅
- 特别是在复杂网格上差异更明显
- 这是因为GPU能更高效地处理索引数据

## 最佳实践

### 何时使用 SoIndexedFaceSet

✅ **推荐使用**：
- 复杂网格（高顶点数）
- 顶点共享度高的模型
- 需要优化内存的场景
- 移动设备或低端硬件

### 何时可以使用 SoFaceSet

✅ **可以使用**：
- 非常简单的几何体
- 顶点几乎不重用
- 动态生成的临时几何体
- 原型开发和快速测试

### 代码示例

```cpp
// 推荐：使用索引优化
SoIndexedFaceSet* createOptimizedMesh()
{
    SoCoordinate3* coords = new SoCoordinate3;
    // 只存储唯一顶点
    coords->point.set1Value(0, ...);
    coords->point.set1Value(1, ...);
    // ...
    
    SoIndexedFaceSet* faceSet = new SoIndexedFaceSet;
    // 通过索引引用顶点
    faceSet->coordIndex.set1Value(0, 0);
    faceSet->coordIndex.set1Value(1, 1);
    faceSet->coordIndex.set1Value(2, 2);
    faceSet->coordIndex.set1Value(3, -1); // 面结束
    // ...
    
    return faceSet;
}
```

## 技术细节

### VBO vs 立即模式对比

```
立即模式 (glVertex*):
┌──────┐      每帧传输      ┌─────┐
│ CPU  │ ─────────────────→ │ GPU │
│ RAM  │   大量数据传输     │     │
└──────┘                    └─────┘

VBO模式:
┌──────┐    首次上传一次     ┌─────────┐
│ CPU  │ ───────────────→   │ GPU显存 │
│ RAM  │                    │ [缓存]  │
└──────┘                    └────┬────┘
                                 │
                            后续帧直接使用
                            (无需重传)
```

### 索引缓冲优化

```
CPU端:                          GPU端:
顶点数组                        顶点缓冲
[V0, V1, V2, V3, ...]    →    [V0, V1, V2, V3, ...]
                                     ↑   ↑   ↑
索引数组                        索引缓冲
[0, 1, 2, 2, 3, 0, ...]    →    [0, 1, 2, 2, 3, 0, ...]
                                     │   │   │
                                重用 │   │   │
                                     └───┴───┘
```

## 相关文档

- [渲染流程详细分析](../../docs/RENDERING_PIPELINE_ANALYSIS.md)
- [渲染流程图示](../../docs/RENDERING_DIAGRAMS.md)
- [渲染流程示例](../rendering_pipeline/)

## 总结

通过本示例，您应该理解：

1. **数据组织的重要性**：合理的数据组织可以显著减少内存使用
2. **索引的优势**：SoIndexedFaceSet 通过索引重用顶点，节省内存和传输带宽
3. **GPU缓存**：索引方式让GPU能够更好地缓存和重用顶点数据
4. **VBO的价值**：现代Coin3D使用VBO技术，数据只需传输一次
5. **性能影响**：特别是在复杂场景中，使用索引可以显著提升性能

选择正确的数据组织方式是3D图形编程中的关键优化点！

# Coin3D 渲染流程示例

## 概述

本示例深入展示了 Coin3D 渲染引擎如何组织场景树数据并将其传输到 GPU 进行渲染。通过实际的代码和控制台输出，您可以清楚地看到场景图遍历、状态累积和 GPU 数据传输的整个过程。

## 示例内容

### 演示1: 状态累积
展示了在没有 `SoSeparator` 隔离的情况下，渲染状态（如变换和材质）如何在场景图中累积传递。

**关键概念**：
- 变换矩阵的累积
- 材质属性的继承
- 状态沿着场景图向下传播

**代码示例**：
```cpp
SoTransform* transform1 = new SoTransform;
transform1->translation.setValue(-4, 2, 0);  // 第一个变换

SoMaterial* material1 = new SoMaterial;
material1->diffuseColor.setValue(1.0, 0.0, 0.0);  // 红色材质

SoSphere* sphere1 = new SoSphere;  // 使用累积的状态

SoTransform* transform2 = new SoTransform;
transform2->translation.setValue(2, 0, 0);  // 第二个变换（累积）

SoSphere* sphere2 = new SoSphere;  // 使用累积的两个变换和红色材质
```

### 演示2: 状态隔离
展示了 `SoSeparator` 节点如何创建独立的状态作用域，防止状态变化影响其他分支。

**关键概念**：
- `SoSeparator` 的状态栈管理
- 状态的入栈和出栈
- 不同对象组之间的状态独立性

**代码示例**：
```cpp
// 第一个独立对象组
SoSeparator* object1 = new SoSeparator;
{
    SoTransform* trans = new SoTransform;
    trans->translation.setValue(0, 2, 0);
    
    SoMaterial* mat = new SoMaterial;
    mat->diffuseColor.setValue(0.0, 1.0, 0.0);  // 绿色
    
    SoCube* cube = new SoCube;
}
// SoSeparator 结束，状态恢复

// 第二个独立对象组（不受第一个影响）
SoSeparator* object2 = new SoSeparator;
{
    // 完全独立的状态
}
```

### 演示3: 自定义几何体
展示了如何创建自定义几何体（金字塔），以及顶点数据如何传输到 GPU。

**关键概念**：
- 顶点坐标的定义
- 索引面集的使用（减少顶点重复）
- 顶点数据的 GPU 传输

**代码示例**：
```cpp
// 定义顶点坐标
SoCoordinate3* coords = new SoCoordinate3;
coords->point.set1Value(0, SbVec3f(0, 1, 0));      // 顶点
coords->point.set1Value(1, SbVec3f(-0.5, 0, 0.5)); // 底面顶点
// ... 更多顶点

// 使用索引定义面（顶点重用）
SoIndexedFaceSet* faceSet = new SoIndexedFaceSet;
faceSet->coordIndex.set1Value(0, 0);  // 第一个三角形
faceSet->coordIndex.set1Value(1, 1);
faceSet->coordIndex.set1Value(2, 2);
faceSet->coordIndex.set1Value(3, -1);  // 面结束标记
```

**GPU 数据传输**：
当渲染这个几何体时，Coin3D 会：
1. 将顶点坐标上传到 GPU（通过 VBO 或顶点数组）
2. 将索引数据上传到 GPU（通过 IBO）
3. 调用 `glDrawElements()` 进行绘制

### 演示4: 嵌套场景图
展示了复杂的嵌套场景图结构，以及子节点如何继承或覆盖父节点的状态。

**关键概念**：
- 场景图的层次结构
- 状态的继承机制
- 状态的覆盖和恢复

**场景图结构**：
```
nestedDemo (SoSeparator)
├── parentTransform (平移)
├── parentMaterial (紫色)
├── child1 (SoSeparator)
│   ├── childTransform (继承父级变换，添加偏移)
│   └── sphere (使用继承的紫色材质)
└── child2 (SoSeparator)
    ├── childTransform
    ├── childMaterial (橙色，覆盖父级材质)
    └── sphere (使用橙色材质)
```

## 运行示例

### 编译

```bash
mkdir build
cd build
cmake .. -DBUILD_COIN3D_EXAMPLES=ON
make rendering_pipeline_example
```

### 运行

```bash
./coin3d_examples/rendering_pipeline/rendering_pipeline_example
```

### 预期输出

运行程序时，您将看到：

1. **控制台输出**：显示每个渲染节点的状态信息
   - 节点名称
   - 累积的变换矩阵
   - 平移和缩放值

2. **3D 窗口**：显示各种几何体
   - 红色球体（演示状态累积）
   - 绿色立方体（独立状态）
   - 蓝色圆锥（独立状态）
   - 黄色金字塔（自定义几何体）
   - 紫色和橙色球体（嵌套结构）

### 示例控制台输出

```
=== Coin3D 渲染流程演示 ===
本示例展示场景图如何组织数据并传输给GPU

--- 演示1: 状态累积（没有 SoSeparator 隔离）---
--- 演示2: 使用 SoSeparator 隔离状态 ---
--- 演示3: 自定义几何体 (展示顶点数据传输) ---
创建自定义几何体（金字塔）:
  顶点数量: 5
  面数量: 5 (4个侧面 + 1个底面)
  这些数据将通过 OpenGL 传输到 GPU

--- 演示4: 嵌套场景图结构 ---
场景图构建完成！

场景图将在渲染时被遍历，
每个节点的状态会累积并通过 OpenGL 传输到 GPU。
请查看上方的状态打印输出。

渲染节点: 球体1 (红色)
  累积变换 - 平移: (-4, 2, 0)
  累积变换 - 缩放: (1, 1, 1)

渲染节点: 球体2 (红色，累积变换)
  累积变换 - 平移: (-2, 2, 0)
  累积变换 - 缩放: (1, 1, 1)

渲染节点: 立方体 (绿色，独立状态)
  累积变换 - 平移: (0, 2, 0)
  累积变换 - 缩放: (1, 1, 1)

...
```

## 渲染流程详解

### 1. 场景图遍历

当 `SoQtExaminerViewer` 需要渲染场景时：

```cpp
viewer->render() 
    ↓
创建 SoGLRenderAction
    ↓
action->apply(root)  // 从根节点开始遍历
```

### 2. 节点处理

对于每个节点，执行以下步骤：

```cpp
// 1. 进入节点（可能保存状态）
if (node is SoSeparator) {
    state->push();  // 保存当前状态到栈
}

// 2. 处理节点
node->GLRender(action);

// 3. 处理子节点
for each child in node {
    traverse(child);  // 递归遍历
}

// 4. 退出节点（可能恢复状态）
if (node is SoSeparator) {
    state->pop();  // 从栈恢复状态
}
```

### 3. 状态累积

```cpp
// SoTransform 节点
void SoTransform::GLRender(SoGLRenderAction* action)
{
    // 获取当前的模型矩阵
    SbMatrix current = SoModelMatrixElement::get(state);
    
    // 计算新的变换矩阵
    SbMatrix transform = calculateTransformMatrix();
    
    // 累积变换（矩阵相乘）
    SbMatrix newMatrix = current * transform;
    
    // 更新状态
    SoModelMatrixElement::set(state, newMatrix);
}
```

### 4. 几何体渲染

```cpp
// SoSphere 节点
void SoSphere::GLRender(SoGLRenderAction* action)
{
    // 1. 获取累积的状态
    SbMatrix modelMatrix = SoModelMatrixElement::get(state);
    SoMaterialElement* material = SoMaterialElement::get(state);
    
    // 2. 应用变换到 OpenGL
    glLoadMatrixf(modelMatrix.getValue());
    
    // 3. 应用材质到 OpenGL
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material->getDiffuseColor());
    
    // 4. 生成球体几何体
    generateSphereGeometry();
    
    // 5. 发送顶点数据到 GPU
    // 方法1: 立即模式
    glBegin(GL_TRIANGLES);
    for (each vertex) {
        glNormal3fv(normal);
        glVertex3fv(vertex);
    }
    glEnd();
    
    // 或方法2: VBO（更高效）
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}
```

### 5. GPU 数据传输

数据传输到 GPU 的主要方式：

#### 方式1: 立即模式（Immediate Mode）
```cpp
glBegin(GL_TRIANGLES);
glVertex3f(x1, y1, z1);  // 每次调用都传输数据到 GPU
glVertex3f(x2, y2, z2);
glVertex3f(x3, y3, z3);
glEnd();
```

#### 方式2: 顶点数组（Vertex Arrays）
```cpp
float vertices[] = { /* 顶点数据 */ };
glVertexPointer(3, GL_FLOAT, 0, vertices);  // 一次传输所有数据
glDrawArrays(GL_TRIANGLES, 0, numVertices);
```

#### 方式3: VBO（Vertex Buffer Objects）- 最高效
```cpp
// 创建并上传到 GPU 内存（只需一次）
glGenBuffers(1, &vboId);
glBindBuffer(GL_ARRAY_BUFFER, vboId);
glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

// 渲染时只需绑定和绘制（不需要重新传输）
glBindBuffer(GL_ARRAY_BUFFER, vboId);
glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
```

## 状态回调说明

本示例使用 `SoCallback` 节点来打印渲染状态：

```cpp
SoCallback* callback = new SoCallback;
callback->setCallback(printRenderState, (void*)"节点名称");

// 在回调函数中
void printRenderState(void* userData, SoAction* action)
{
    // 获取当前渲染状态
    SoState* state = action->getState();
    SbMatrix matrix = SoModelMatrixElement::get(state);
    
    // 打印状态信息
    std::cout << "当前节点: " << (char*)userData << std::endl;
    std::cout << "累积变换: " << matrix << std::endl;
}
```

这个回调在场景图遍历时被调用，让我们可以观察到渲染流程的内部状态。

## 性能优化提示

通过本示例，您可以了解如何优化场景图以提高渲染性能：

### 1. 减少状态切换
```cpp
// 不好：频繁切换材质
for each object {
    addChild(new SoMaterial);  // GPU 状态切换成本高
    addChild(object);
}

// 好：按材质分组
addChild(new SoMaterial);  // 红色
addChild(objects with red material...);
addChild(new SoMaterial);  // 蓝色
addChild(objects with blue material...);
```

### 2. 使用 SoSeparator 合理分组
```cpp
// 使用 SoSeparator 可以：
// - 隔离状态，避免不必要的状态累积
// - 启用缓存（renderCaching）
// - 优化视锥体剔除

SoSeparator* group = new SoSeparator;
group->renderCaching = SoSeparator::ON;  // 启用缓存
```

### 3. 使用索引面集
```cpp
// 使用 SoIndexedFaceSet 而不是 SoFaceSet
// - 减少顶点重复
// - 降低内存使用
// - 提高 GPU 缓存效率
```

## 学习要点

通过本示例，您应该理解：

1. **场景图结构**：如何组织 3D 场景的层次结构
2. **遍历机制**：Coin3D 如何遍历场景图
3. **状态管理**：渲染状态如何累积和传播
4. **状态隔离**：SoSeparator 如何创建独立的状态作用域
5. **几何数据**：顶点数据如何定义和传输
6. **GPU 传输**：数据如何从 CPU 传输到 GPU
7. **性能优化**：如何组织场景图以提高性能

## 相关文档

- [渲染流程详细分析](../../docs/RENDERING_PIPELINE_ANALYSIS.md)
- [场景图示例](../scene_graph/)
- [变换示例](../transformations/)
- [材质示例](../materials/)

## 总结

本示例通过实际代码和控制台输出，直观地展示了 Coin3D 渲染引擎的核心工作原理。理解这些概念对于高效使用 Coin3D 创建复杂的 3D 应用至关重要。

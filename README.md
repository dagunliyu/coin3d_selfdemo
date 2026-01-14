# MeshEditor - Coin3D Examples

这个仓库包含使用 Coin3D 渲染引擎的示例代码，使用 CMake 进行组织。

## 📚 渲染引擎分析

**NEW!** 本仓库现在包含 Coin3D 渲染引擎的深入分析文档和示例代码：

- **[渲染流程详细分析](docs/RENDERING_PIPELINE_ANALYSIS.md)** - 深入解析 Coin3D 如何组织场景树数据并传输到 GPU
  - 场景图架构详解
  - 渲染流程和遍历机制
  - 状态管理系统
  - GPU 数据传输方式
  - 性能优化策略

- **[渲染流程图示说明](docs/RENDERING_DIAGRAMS.md)** - 通过图示和示例帮助理解渲染流程
  - 整体架构图
  - 场景图结构示例
  - 渲染流程时序图
  - GPU 数据传输方式对比
  - 性能优化策略示意图

- **[渲染流程示例代码](coin3d_examples/rendering_pipeline/)** - 实际代码演示渲染流程
  - 状态累积演示
  - 状态隔离演示
  - 自定义几何体和 GPU 数据传输
  - 嵌套场景图结构

- **[GPU数据传输示例代码](coin3d_examples/gpu_data_transfer/)** - 性能优化实践
  - 顶点数据组织方式对比
  - 索引优化实例
  - 内存和性能统计

## 项目结构

项目按照 Coin3D 的不同功能特性组织成不同的目录：

```
coin3d_examples/
├── basic_shapes/         # 基本形状示例 (球体、立方体、圆锥、圆柱)
├── scene_graph/          # 场景图操作示例
├── transformations/      # 变换示例 (平移、旋转、缩放)
├── materials/            # 材质和外观示例
├── lighting/             # 光源示例 (定向光、点光源、聚光灯)
├── cameras/              # 相机操作示例
├── text/                 # 文本渲染示例
├── events/               # 事件处理和交互示例
├── file_io/              # 文件读写示例
├── animation/            # 动画示例
├── rendering_pipeline/   # 渲染流程深入分析示例 ⭐ NEW
└── gpu_data_transfer/    # GPU数据传输优化示例 ⭐ NEW
```

## 依赖项

### 必需依赖

- **CMake** (>= 3.15)
- **Coin3D** - 3D 图形库
- **SoQt** - Coin3D 的 Qt 绑定
- **Qt** (Qt5 或 Qt6)
- **C++ 编译器** (支持 C++17)

### 安装依赖 (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install libcoin-dev
sudo apt-get install libsoqt-dev
sudo apt-get install qtbase5-dev
```

### 安装依赖 (macOS with Homebrew)

```bash
brew install cmake
brew install coin
brew install soqt
brew install qt
```

### 安装依赖 (Windows)

在 Windows 上，您可以：
1. 从 [Coin3D 官方网站](https://github.com/coin3d/coin) 下载并安装 Coin3D
2. 从 [Qt 官方网站](https://www.qt.io/) 下载并安装 Qt
3. 使用 vcpkg 安装依赖：
   ```
   vcpkg install coin3d soqt
   ```

## 构建

### 标准构建流程

```bash
# 克隆仓库
git clone <repository-url>
cd MeshEditor

# 创建构建目录
mkdir build
cd build

# 配置 CMake (启用 Coin3D 示例)
cmake .. -DBUILD_COIN3D_EXAMPLES=ON

# 编译
cmake --build .

# 或者使用 make
make
```

### 启用 Coin3D 示例

在根目录的 `CMakeLists.txt` 中，取消注释以下行：

```cmake
# add_subdirectory(coin3d_examples)
```

改为：

```cmake
add_subdirectory(coin3d_examples)
```

然后重新运行 CMake 配置和构建。

## 运行示例

构建完成后，可执行文件将位于构建目录中。例如：

```bash
# 运行基本形状示例
./coin3d_examples/basic_shapes/basic_shapes_example

# 运行动画示例
./coin3d_examples/animation/animation_example

# 运行材质示例
./coin3d_examples/materials/materials_example

# 运行渲染流程分析示例 (NEW!)
./coin3d_examples/rendering_pipeline/rendering_pipeline_example
```

## 示例说明

### 1. Basic Shapes (基本形状)
展示如何创建 Coin3D 的基本几何体：球体、立方体、圆锥和圆柱。

### 2. Scene Graph (场景图)
演示场景图的层次结构和组织方式，展示父子关系和分组。

### 3. Transformations (变换)
展示各种变换操作：平移、旋转、缩放以及组合变换。

### 4. Materials (材质)
演示材质属性：漫反射颜色、镜面反射颜色、自发光颜色和透明度。

### 5. Lighting (光照)
展示不同类型的光源：定向光、点光源和聚光灯。

### 6. Cameras (相机)
演示相机设置和操作，包括透视相机和正交相机。

### 7. Text (文本)
展示 Coin3D 中的文本渲染，包括 2D 文本和 3D 文本。

### 8. Events (事件)
演示事件处理和用户交互，包括鼠标事件、键盘事件和对象选择。

### 9. File I/O (文件输入输出)
展示如何读取和写入 3D 场景文件 (Inventor 格式)。

### 10. Animation (动画)
演示使用引擎和定时器创建动画效果。

### 11. Rendering Pipeline (渲染流程) ⭐ NEW
**深入分析 Coin3D 渲染引擎的核心工作原理**：
- 场景图遍历过程的可视化演示
- 渲染状态的累积和传播机制
- SoSeparator 的状态隔离功能
- 自定义几何体的顶点数据传输
- 嵌套场景图的状态管理
- 实时打印渲染状态信息

**特别说明**：此示例配合 [渲染流程详细分析文档](docs/RENDERING_PIPELINE_ANALYSIS.md) 使用，可以帮助您深入理解 Coin3D 如何将场景树数据组织并发送给 GPU。

### 12. GPU Data Transfer (GPU数据传输) ⭐ NEW
**演示不同的几何数据组织方式及其对GPU传输的影响**：
- FaceSet vs IndexedFaceSet 内存使用对比
- 顶点索引重用的优势
- 复杂网格的性能优化
- VBO (Vertex Buffer Objects) 技术
- 实际数据传输统计和性能分析

**特别说明**：通过直观的对比演示，理解如何优化几何数据以提高渲染性能。

## 故障排除

### CMake 找不到 Coin3D

如果 CMake 无法找到 Coin3D，您可能需要设置 `CMAKE_PREFIX_PATH`：

```bash
cmake .. -DCMAKE_PREFIX_PATH=/path/to/coin3d/installation
```

### 链接错误

确保所有依赖库都已正确安装，并且版本兼容。

## 贡献

欢迎提交问题报告和拉取请求！

## 许可证

请参阅项目的许可证文件。

## 参考资源

- [Coin3D 官方文档](https://github.com/coin3d/coin/wiki)
- [Coin3D API 参考](https://coin3d.github.io/Coin/html/)
- [Open Inventor 编程指南](https://developer.openinventor.com/)

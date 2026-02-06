# MeshEditor - Coin3D & Dawn Examples

这个仓库包含使用 Coin3D 渲染引擎和 Dawn (WebGPU) 的示例代码，使用 CMake 进行组织。

## 项目结构

项目包含两类示例：

### Coin3D 示例

```
coin3d_examples/
├── basic_shapes/      # 基本形状示例 (球体、立方体、圆锥、圆柱)
├── scene_graph/       # 场景图操作示例
├── transformations/   # 变换示例 (平移、旋转、缩放)
├── materials/         # 材质和外观示例
├── lighting/          # 光源示例 (定向光、点光源、聚光灯)
├── cameras/           # 相机操作示例
├── text/              # 文本渲染示例
├── events/            # 事件处理和交互示例
├── file_io/           # 文件读写示例
└── animation/         # 动画示例
```

### Dawn (WebGPU) 示例

```
dawn_examples/
├── triangle_demo.cpp  # 基本三角形渲染示例
├── shapes_demo.cpp    # 3D 形状渲染示例 (立方体、金字塔等)
└── README.md          # Dawn 示例详细文档
```

## 依赖项

### Coin3D 示例依赖

- **CMake** (>= 3.15)
- **Coin3D** - 3D 图形库
- **SoQt** - Coin3D 的 Qt 绑定
- **Qt** (Qt5 或 Qt6)
- **C++ 编译器** (支持 C++17)

### Dawn 示例依赖

- **CMake** (>= 3.15)
- **GLFW** - 窗口管理库
- **Dawn** - WebGPU 实现（作为 Git 子模块包含）
- **C++ 编译器** (支持 C++17)

### 安装依赖 (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install cmake

# Coin3D 依赖
sudo apt-get install libcoin-dev
sudo apt-get install libsoqt-dev
sudo apt-get install qtbase5-dev

# Dawn 依赖
sudo apt-get install libglfw3-dev
sudo apt-get install libx11-dev
```

### 安装依赖 (macOS with Homebrew)

```bash
brew install cmake

# Coin3D 依赖
brew install coin
brew install soqt
brew install qt

# Dawn 依赖
brew install glfw
```

### 安装依赖 (Windows)

在 Windows 上，您可以：

**Coin3D:**
1. 从 [Coin3D 官方网站](https://github.com/coin3d/coin) 下载并安装 Coin3D
2. 从 [Qt 官方网站](https://www.qt.io/) 下载并安装 Qt
3. 使用 vcpkg 安装依赖：
   ```
   vcpkg install coin3d soqt
   ```

**Dawn:**
1. 使用 vcpkg 安装 GLFW：
   ```
   vcpkg install glfw3
   ```

## 构建

### 初始化子模块

首次克隆仓库后，需要初始化 Git 子模块（包括 Coin3D 和 Dawn）：

```bash
git clone <repository-url>
cd coin3d_selfdemo
git submodule update --init --recursive
```

**注意**: Dawn 是一个大型项目，初次下载可能需要一些时间。

### 标准构建流程

```bash
# 创建构建目录
mkdir build
cd build

# 配置 CMake
# 构建所有示例（Coin3D + Dawn）
cmake ..

# 或者只构建 Coin3D 示例
cmake .. -DBUILD_DAWN_EXAMPLES=OFF

# 或者只构建 Dawn 示例
cmake .. -DBUILD_COIN_FROM_SOURCE=OFF

# 编译
cmake --build .

# 或者使用 make
make
```

**注意**: 第一次构建 Dawn 可能需要较长时间（10-30分钟），因为它会下载并编译所有依赖项。

### 构建选项

在 CMake 配置时，可以使用以下选项：

- `BUILD_COIN_FROM_SOURCE`: 从源代码构建 Coin3D（默认: ON）
- `BUILD_DAWN_EXAMPLES`: 构建 Dawn 示例（默认: ON）

## 运行示例

构建完成后，可执行文件将位于构建目录中。

### Coin3D 示例

```bash
# 运行基本形状示例
./coin3d_examples/basic_shapes/basic_shapes_example

# 运行动画示例
./coin3d_examples/animation/animation_example

# 运行材质示例
./coin3d_examples/materials/materials_example
```

### Dawn 示例

```bash
# 运行三角形示例
./dawn_examples/dawn_triangle_demo

# 运行形状示例（3D 立方体等）
./dawn_examples/dawn_shapes_demo
```

详细的 Dawn 示例说明请查看 [dawn_examples/README.md](dawn_examples/README.md)

## 示例说明

### Coin3D 示例

#### 1. Basic Shapes (基本形状)
展示如何创建 Coin3D 的基本几何体：球体、立方体、圆锥和圆柱。

#### 2. Scene Graph (场景图)
演示场景图的层次结构和组织方式，展示父子关系和分组。

#### 3. Transformations (变换)
展示各种变换操作：平移、旋转、缩放以及组合变换。

#### 4. Materials (材质)
演示材质属性：漫反射颜色、镜面反射颜色、自发光颜色和透明度。

#### 5. Lighting (光照)
展示不同类型的光源：定向光、点光源和聚光灯。

#### 6. Cameras (相机)
演示相机设置和操作，包括透视相机和正交相机。

#### 7. Text (文本)
展示 Coin3D 中的文本渲染，包括 2D 文本和 3D 文本。

#### 8. Events (事件)
演示事件处理和用户交互，包括鼠标事件、键盘事件和对象选择。

#### 9. File I/O (文件输入输出)
展示如何读取和写入 3D 场景文件 (Inventor 格式)。

#### 10. Animation (动画)
演示使用引擎和定时器创建动画效果。

### Dawn (WebGPU) 示例

#### 1. Triangle Demo (三角形示例)
- 演示 Dawn 的基本使用
- 创建渲染管线
- 使用 WGSL 着色器
- 渲染一个红色三角形

#### 2. Shapes Demo (形状示例)
- 渲染 3D 形状（立方体、金字塔）
- 顶点缓冲区和索引缓冲区
- 3D 变换和旋转动画
- 彩色顶点属性

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

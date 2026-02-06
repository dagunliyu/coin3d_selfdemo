# Dawn 示例

本目录包含使用 Dawn (Google 的 WebGPU 实现) 渲染图形的示例代码。

## 什么是 Dawn?

Dawn 是 Google 开发的 WebGPU 的 C++ 实现。WebGPU 是一个现代的跨平台图形 API，提供了对 GPU 的直接访问，支持高性能的 3D 图形渲染和通用计算。

## 依赖项

### 必需依赖

- **CMake** (>= 3.15)
- **Dawn** - WebGPU 实现 (作为 Git 子模块包含)
- **GLFW** - 跨平台窗口库
- **C++ 编译器** (支持 C++17)

### 安装依赖 (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install libglfw3-dev
sudo apt-get install libx11-dev
```

### 安装依赖 (macOS with Homebrew)

```bash
brew install cmake
brew install glfw
```

### 安装依赖 (Windows)

在 Windows 上，您可以：
1. 使用 vcpkg 安装 GLFW：
   ```
   vcpkg install glfw3
   ```
2. 或从 [GLFW 官网](https://www.glfw.org/) 下载预编译的库

## 构建

### 初始化 Dawn 子模块

首次克隆仓库后，需要初始化 Dawn 子模块：

```bash
cd coin3d_selfdemo
git submodule update --init --recursive
```

**注意**: Dawn 是一个大型项目，下载可能需要一些时间。

### 构建示例

```bash
# 创建构建目录
mkdir build
cd build

# 配置 CMake
cmake .. -DBUILD_DAWN_EXAMPLES=ON

# 编译
cmake --build .

# 或者使用 make
make
```

构建 Dawn 第一次可能需要较长时间，因为它会下载并编译所有依赖项。

### 禁用 Dawn 示例

如果不想构建 Dawn 示例，可以在配置时禁用：

```bash
cmake .. -DBUILD_DAWN_EXAMPLES=OFF
```

## 运行示例

构建完成后，可执行文件将位于构建目录中：

```bash
# 运行三角形示例
./dawn_examples/dawn_triangle_demo

# 运行形状示例
./dawn_examples/dawn_shapes_demo
```

## 示例说明

### 1. Triangle Demo (triangle_demo.cpp)

**功能**: 最基本的 Dawn 示例，演示如何：
- 初始化 Dawn 和 WebGPU
- 创建渲染管线
- 使用 WGSL 着色器
- 渲染一个简单的红色三角形

**适合**: 初学者了解 Dawn 的基本使用流程

### 2. Shapes Demo (shapes_demo.cpp)

**功能**: 更高级的 3D 图形示例，演示如何：
- 创建顶点缓冲区和索引缓冲区
- 渲染 3D 形状（立方体、金字塔）
- 使用统一缓冲区进行 3D 变换
- 实现旋转动画
- 使用颜色顶点属性

**适合**: 了解 3D 图形基础和 Dawn 的高级特性

## Dawn vs Coin3D

| 特性 | Dawn (WebGPU) | Coin3D |
|------|---------------|---------|
| API 类型 | 现代低级 GPU API | 高级场景图 API |
| 学习曲线 | 较陡峭 | 较平缓 |
| 控制程度 | 完全控制 | 抽象层较高 |
| 性能 | 可以达到最优 | 良好但有抽象开销 |
| 跨平台 | 是（通过 WebGPU） | 是 |
| 主要用途 | 现代图形应用、游戏 | CAD、科学可视化 |

## 代码结构

每个示例程序都包含：

1. **着色器代码**: 使用 WGSL (WebGPU Shading Language) 编写
2. **初始化代码**: 设置 Dawn、创建窗口、配置交换链
3. **资源创建**: 创建缓冲区、纹理、管线等
4. **渲染循环**: 每帧更新和绘制场景
5. **清理代码**: 释放资源

## 故障排除

### CMake 找不到 Dawn

确保已经初始化了 Git 子模块：
```bash
git submodule update --init --recursive
```

### 找不到 GLFW

安装 GLFW 开发库：
```bash
# Ubuntu/Debian
sudo apt-get install libglfw3-dev

# macOS
brew install glfw
```

### 编译错误

Dawn 需要支持 C++17 的编译器：
- GCC >= 7
- Clang >= 5
- MSVC >= 2017

### 运行时错误

确保您的系统支持 Vulkan、D3D12 或 Metal（取决于平台）。

## 学习资源

- [WebGPU 规范](https://www.w3.org/TR/webgpu/)
- [Dawn 文档](https://dawn.googlesource.com/dawn)
- [WGSL 语言规范](https://www.w3.org/TR/WGSL/)
- [WebGPU 示例](https://webgpu.github.io/webgpu-samples/)

## 贡献

欢迎提交问题报告和拉取请求！如果您创建了新的有趣的 Dawn 示例，请随时贡献。

## 许可证

请参阅项目根目录的许可证文件。Dawn 本身使用 Apache 2.0 许可证。

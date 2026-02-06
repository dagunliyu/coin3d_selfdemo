# Dawn 集成说明

本文档说明了 Dawn (WebGPU) 作为第三方库的集成方式。

## 集成方式

Dawn 通过 Git 子模块的方式集成到本项目中：

```
external/dawn/  # Dawn 源代码（Git 子模块）
```

## 为什么选择 Dawn？

Dawn 是 Google 开发的 WebGPU C++ 实现，具有以下优势：

1. **现代化**: 基于现代图形 API 设计理念
2. **跨平台**: 支持 Windows、Linux、macOS
3. **高性能**: 直接访问 GPU，性能优秀
4. **WebGPU 标准**: 符合 W3C WebGPU 标准
5. **活跃维护**: Google Chrome 团队维护

## 与 Coin3D 的对比

| 特性 | Dawn | Coin3D |
|------|------|--------|
| API 层级 | 低级（类似 Vulkan/Metal） | 高级（场景图） |
| 学习曲线 | 陡峭 | 平缓 |
| 灵活性 | 高 | 中等 |
| 开发效率 | 较低（需要更多代码） | 高 |
| 性能潜力 | 最优 | 良好 |
| 适用场景 | 游戏、实时渲染 | CAD、科学可视化 |

## 目录结构

```
coin3d_selfdemo/
├── external/
│   ├── coin/          # Coin3D 子模块
│   └── dawn/          # Dawn 子模块
├── coin3d_examples/   # Coin3D 示例
├── dawn_examples/     # Dawn 示例
│   ├── triangle_demo.cpp   # 三角形示例
│   ├── shapes_demo.cpp     # 3D 形状示例
│   ├── CMakeLists.txt      # Dawn 示例构建配置
│   └── README.md           # Dawn 示例文档
├── CMakeLists.txt     # 主 CMake 配置
└── README.md          # 主文档
```

## 构建系统

### CMake 配置

主 CMakeLists.txt 中添加了以下选项：

```cmake
option(BUILD_DAWN_EXAMPLES "Build Dawn (WebGPU) examples" ON)
```

### 依赖管理

Dawn 的依赖通过其内部的依赖管理系统自动下载和构建。主要依赖包括：

- SPIRV-Tools
- SPIRV-Cross  
- Tint (WGSL 编译器)
- 平台特定的图形 API（Vulkan/D3D12/Metal）

### 构建选项

在 dawn_examples/CMakeLists.txt 中配置了以下选项以优化构建：

```cmake
set(DAWN_FETCH_DEPENDENCIES ON)      # 自动获取依赖
set(DAWN_BUILD_SAMPLES OFF)          # 不构建 Dawn 官方示例
set(DAWN_BUILD_NODE_BINDINGS OFF)    # 不构建 Node.js 绑定
set(TINT_BUILD_TESTS OFF)            # 不构建 Tint 测试
```

## 示例说明

### Triangle Demo (triangle_demo.cpp)

演示基础的 Dawn 使用：
- 初始化 Dawn 实例
- 创建渲染设备和交换链
- 编写 WGSL 着色器
- 创建渲染管线
- 绘制三角形

### Shapes Demo (shapes_demo.cpp)

演示 3D 图形渲染：
- 创建顶点缓冲区和索引缓冲区
- 使用统一缓冲区传递变换矩阵
- 渲染立方体和金字塔
- 实现旋转动画

## 开发指南

### 添加新的 Dawn 示例

1. 在 `dawn_examples/` 目录下创建新的 `.cpp` 文件
2. 在 `dawn_examples/CMakeLists.txt` 中添加新的可执行文件：

```cmake
add_executable(my_demo my_demo.cpp)
target_link_libraries(my_demo ${DAWN_LIBRARIES} glfw)
target_include_directories(my_demo PRIVATE ${DAWN_INCLUDE_DIRS})
```

### WGSL 着色器编写

Dawn 使用 WGSL (WebGPU Shading Language) 编写着色器。基本结构：

```wgsl
// 顶点着色器
@vertex
fn vs_main(@builtin(vertex_index) index: u32) -> @builtin(position) vec4f {
    // 顶点处理逻辑
    return vec4f(0.0, 0.0, 0.0, 1.0);
}

// 片段着色器
@fragment
fn fs_main() -> @location(0) vec4f {
    // 像素颜色计算
    return vec4f(1.0, 0.0, 0.0, 1.0);
}
```

### 调试技巧

1. **启用验证层**: 在 Debug 模式下，Dawn 会启用详细的验证
2. **检查错误**: 使用设备错误回调函数捕获错误
3. **WGSL 编译错误**: Tint 编译器会提供详细的错误信息

## 性能优化

### 构建优化

第一次构建 Dawn 会很慢，可以通过以下方式优化：

1. **使用 ninja**: `cmake -G Ninja ..`
2. **并行编译**: `cmake --build . -j$(nproc)`
3. **增量构建**: 后续构建会快很多

### 运行时优化

1. **选择合适的后端**: Dawn 会自动选择最佳的图形后端（Vulkan/D3D12/Metal）
2. **批量绘制**: 减少绘制调用次数
3. **使用实例化**: 绘制多个相同物体时使用实例化
4. **优化着色器**: 避免在片段着色器中进行复杂计算

## 平台支持

Dawn 支持以下平台和图形后端：

| 平台 | 图形后端 | 状态 |
|------|---------|------|
| Linux | Vulkan | ✅ 完全支持 |
| Windows | D3D12, Vulkan | ✅ 完全支持 |
| macOS | Metal | ✅ 完全支持 |
| iOS | Metal | ⚠️ 实验性支持 |
| Android | Vulkan | ⚠️ 实验性支持 |

## 常见问题

### Q: Dawn 构建失败？

A: 确保满足以下条件：
- CMake >= 3.15
- 支持 C++17 的编译器
- 网络连接正常（需要下载依赖）
- 足够的磁盘空间（约 2-3 GB）

### Q: 找不到 GLFW？

A: 安装 GLFW 开发库：
```bash
# Ubuntu/Debian
sudo apt-get install libglfw3-dev

# macOS
brew install glfw
```

### Q: 运行时找不到共享库？

A: 设置 LD_LIBRARY_PATH（Linux）或 DYLD_LIBRARY_PATH（macOS）指向构建目录。

## 学习资源

- [WebGPU 官方规范](https://www.w3.org/TR/webgpu/)
- [Dawn 源码](https://dawn.googlesource.com/dawn)
- [WGSL 规范](https://www.w3.org/TR/WGSL/)
- [WebGPU 示例集](https://webgpu.github.io/webgpu-samples/)
- [Learn WebGPU](https://eliemichel.github.io/LearnWebGPU/)

## 许可证

Dawn 使用 Apache 2.0 许可证。详情请查看 `external/dawn/LICENSE`。

## 更新 Dawn

更新 Dawn 子模块到最新版本：

```bash
cd external/dawn
git pull origin main
cd ../..
git add external/dawn
git commit -m "Update Dawn to latest version"
```

## 贡献

如果您创建了新的 Dawn 示例或改进了现有示例，欢迎提交 PR！

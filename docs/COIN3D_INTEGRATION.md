# Coin3D 集成构建说明

## 概述

本仓库已集成 Coin3D 源码作为子模块，可以与主项目一起编译。这样做的优势：

1. **统一构建**：一次构建命令即可编译 Coin3D 和所有示例
2. **源码调试**：可以在 IDE 中直接调试 Coin3D 源码
3. **输出管理**：所有输出文件（DLL、PDB等）统一到 `bin/` 目录
4. **版本控制**：通过 Git 子模块管理 Coin3D 版本

## 项目结构

```
coin3d_selfdemo/
├── thirdparty/
│   └── coin/              # Coin3D 源码（Git 子模块）
├── coin3d_examples/       # 示例代码
├── bin/                   # 输出目录（DLL、EXE、PDB）
├── lib/                   # 静态库输出目录
└── CMakeLists.txt         # 主构建配置
```

## 构建步骤

### 1. 克隆仓库（包含子模块）

```bash
# 新克隆（自动初始化子模块）
git clone --recursive https://github.com/dagunliyu/coin3d_selfdemo.git

# 或者，如果已经克隆，需要初始化子模块
git submodule update --init --recursive
```

### 2. 配置和编译

```bash
# 创建构建目录
mkdir build
cd build

# 配置 CMake
cmake ..

# 编译（所有项目，包括 Coin3D）
cmake --build . --config Release

# 或者使用 Visual Studio 时
cmake .. -G "Visual Studio 16 2019"  # 或其他版本
cmake --build . --config Debug  # 编译 Debug 版本
```

### 3. 输出位置

编译完成后，所有文件会输出到：

```
build/
├── bin/
│   ├── Coin.dll           # Coin3D 动态库
│   ├── Coin.pdb           # Coin3D 调试符号（Debug 模式）
│   ├── basic_shapes_example.exe
│   ├── rendering_pipeline_example.exe
│   └── ...                # 其他示例程序
└── lib/
    └── Coin.lib           # Coin3D 导入库
```

## IDE 调试配置

### Visual Studio

1. **打开项目**：
   ```bash
   # 在 build 目录生成解决方案
   cmake .. -G "Visual Studio 16 2019"
   ```

2. **打开解决方案**：
   - 打开 `build/coin3d_example.sln`

3. **设置启动项目**：
   - 在解决方案资源管理器中右键选择示例项目（如 `rendering_pipeline_example`）
   - 选择"设为启动项目"

4. **调试 Coin3D 源码**：
   - Coin3D 源码在解决方案中可见（Coin 项目）
   - 可以在 Coin3D 源文件中设置断点
   - 运行调试时会自动进入 Coin3D 代码

5. **配置工作目录**（如果需要）：
   - 右键项目 → 属性 → 调试
   - 设置"工作目录"为 `$(OutDir)` 或项目根目录

### Visual Studio Code

1. **打开文件夹**：
   ```bash
   code /path/to/coin3d_selfdemo
   ```

2. **安装扩展**：
   - C/C++ (Microsoft)
   - CMake Tools

3. **配置 CMake**：
   - 按 `Ctrl+Shift+P`，选择 "CMake: Configure"
   - 选择工具链（如 Visual Studio 或 GCC）

4. **构建**：
   - 按 `Ctrl+Shift+P`，选择 "CMake: Build"

5. **调试**：
   - 创建 `.vscode/launch.json`：
   ```json
   {
       "version": "0.2.0",
       "configurations": [
           {
               "name": "Debug Example",
               "type": "cppvsdbg",  // Windows 使用 cppvsdbg，Linux 使用 cppdbg
               "request": "launch",
               "program": "${workspaceFolder}/build/bin/rendering_pipeline_example.exe",
               "args": [],
               "stopAtEntry": false,
               "cwd": "${workspaceFolder}/build/bin",
               "environment": [],
               "externalConsole": false
           }
       ]
   }
   ```

## CMake 配置选项

可以在配置时自定义 Coin3D 的构建选项：

```bash
# 构建静态库而非动态库
cmake .. -DCOIN_BUILD_SHARED_LIBS=OFF

# 启用线程安全
cmake .. -DCOIN_THREADSAFE=ON

# 禁用 VRML97 支持
cmake .. -DHAVE_VRML97=OFF

# 使用 Release 配置（优化）
cmake .. -DCMAKE_BUILD_TYPE=Release

# Windows 上指定生成器和平台
cmake .. -G "Visual Studio 16 2019" -A x64
```

## 常见问题

### Q1: 子模块未下载

**问题**：编译时提示找不到 `thirdparty/coin` 目录

**解决**：
```bash
git submodule update --init --recursive
```

### Q2: DLL 找不到

**问题**：运行示例时提示找不到 Coin.dll

**解决**：所有 DLL 已输出到 `build/bin/` 目录，确保从该目录运行可执行文件，或将该目录添加到 PATH。

### Q3: 调试时无法进入 Coin3D 源码

**问题**：设置断点无效或显示"无可用源"

**解决**：
- 确保使用 Debug 配置编译：`cmake --build . --config Debug`
- 检查 PDB 文件是否在 `build/bin/` 目录
- Visual Studio 中，工具 → 选项 → 调试 → 符号，添加 `build/bin` 目录

### Q4: CMake 配置失败

**问题**：CMake 找不到 OpenGL 或其他依赖

**解决**：
- Windows：确保安装了 Windows SDK
- Linux：安装开发包 `sudo apt-get install libgl1-mesa-dev`
- macOS：Xcode 命令行工具 `xcode-select --install`

### Q5: 编译 Coin3D 时出错

**问题**：Coin3D 编译失败

**解决**：
- 检查编译器版本（需要支持 C++11）
- 查看 `thirdparty/coin/README.md` 了解依赖
- 尝试更新子模块：`git submodule update --remote`

## 更新 Coin3D 版本

更新到最新版本：

```bash
cd thirdparty/coin
git pull origin master
cd ../..
git add thirdparty/coin
git commit -m "Update Coin3D to latest version"
```

切换到特定版本：

```bash
cd thirdparty/coin
git checkout v4.0.0  # 或其他 tag/commit
cd ../..
git add thirdparty/coin
git commit -m "Update Coin3D to v4.0.0"
```

## 技术细节

### 输出目录配置

在主 `CMakeLists.txt` 中配置：

```cmake
# 所有可执行文件和 DLL 输出到 bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 静态库输出到 lib/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
```

### Coin3D 集成

```cmake
# 配置 Coin3D 选项
set(COIN_BUILD_SHARED_LIBS ON CACHE BOOL "Build Coin3D as shared library")
set(COIN_BUILD_TESTS OFF CACHE BOOL "Skip Coin3D tests")

# 添加为子项目
add_subdirectory(thirdparty/coin)

# 导出变量供示例使用
set(COIN_LIBRARY Coin CACHE INTERNAL "Coin3D library target")
set(COIN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/coin/include)
```

### 示例链接

示例项目直接链接 Coin3D 目标：

```cmake
target_link_libraries(my_example
    Coin::Coin      # 使用内部构建的 Coin3D
    SoQt::SoQt      # 外部 SoQt（如果需要）
)
```

## 优势总结

1. **一键构建**：`cmake --build .` 编译所有内容
2. **源码可见**：可以直接查看和修改 Coin3D 源码
3. **调试方便**：断点可以进入 Coin3D 内部
4. **版本锁定**：Git 子模块确保版本一致性
5. **输出集中**：所有输出在 `bin/` 目录，便于管理
6. **跨平台**：Windows、Linux、macOS 统一构建流程

## 参考资料

- [Coin3D 官方文档](https://github.com/coin3d/coin)
- [CMake 子模块文档](https://cmake.org/cmake/help/latest/command/add_subdirectory.html)
- [Git 子模块教程](https://git-scm.com/book/en/v2/Git-Tools-Submodules)

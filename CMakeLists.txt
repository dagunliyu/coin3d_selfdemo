cmake_minimum_required(VERSION 3.16)
project(coin3d_selfdemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coin3D 构建选项
option(BUILD_COIN_FROM_SOURCE "Build Coin3D from source" ON)

# Dawn 构建选项
option(BUILD_DAWN_EXAMPLES "Build Dawn (WebGPU) examples" ON)

if(BUILD_COIN_FROM_SOURCE)
    # 设置 Coin3D 构建选项
    set(COIN_BUILD_SHARED_LIBS ON CACHE BOOL "Build Coin3D as shared library" FORCE)
    set(COIN_BUILD_TESTS OFF CACHE BOOL "Disable Coin3D tests" FORCE)
    set(COIN_BUILD_DOCUMENTATION OFF CACHE BOOL "Disable Coin3D documentation" FORCE)
    
    # 添加 Coin3D 子目录
    add_subdirectory(external/coin)
    
    # 设置变量供后续使用
    set(COIN_FOUND TRUE)
    set(COIN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/coin/include ${CMAKE_BINARY_DIR}/external/coin)
    set(COIN_LIBRARY Coin)
else(BUILD_COIN_FROM_SOURCE)
    # 使用系统安装的 Coin3D
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cMake")
    find_package(Coin REQUIRED)
endif()

include(cMake)
add_subdirectory(cMake/cmakeHelper) # must have a CMakeLists

SetupOpenGL()

# Coin3D examples - organized by features
add_subdirectory(coin3d_examples)

# Dawn examples - WebGPU demos
if(BUILD_DAWN_EXAMPLES)
    add_subdirectory(dawn_examples)
endif()

# https://www.coin3d.org/quarter/
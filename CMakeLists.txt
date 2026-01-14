cmake_minimum_required(VERSION 3.15)
project(MeshEditor)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cMake)
add_subdirectory(cMake/cmakeHelper) # must have a CMakeLists

SetupOpenGL()


# set bin
if(WIN32)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin CACHE PATH "Dir of bin")
endif(WIN32)

# config SDK_DIR
add_subdirectory(sdk)

# make sure cmake can find the desired *.cmake file
set(GLDepends_DIR "${SDK_DIR}/cmake" CACHE PATH "")
find_package(GLDepends)

# gltest code
add_subdirectory(gltest)

# Coin3D examples - organized by features
# Uncomment to build Coin3D examples when Coin3D is installed
# add_subdirectory(coin3d_examples)

# 添加主程序源文件（请根据实际情况修改）
add_executable(MeshEditor main.cpp)

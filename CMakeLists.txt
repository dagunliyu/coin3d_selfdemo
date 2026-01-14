cmake_minimum_required(VERSION 3.15)
project(coin3d_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cMake)
add_subdirectory(cMake/cmakeHelper) # must have a CMakeLists

SetupOpenGL()

# Coin3D examples - organized by features
add_subdirectory(coin3d_examples)

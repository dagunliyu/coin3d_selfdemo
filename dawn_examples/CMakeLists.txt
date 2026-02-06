# Dawn Examples
# This directory contains examples demonstrating Dawn (WebGPU) usage
cmake_minimum_required(VERSION 3.15)

# Add Dawn library as subdirectory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../external/dawn/CMakeLists.txt")
    message(STATUS "Building Dawn from source...")
    
    # Set Dawn build options before adding subdirectory - disable unnecessary features for faster builds
    set(DAWN_FETCH_DEPENDENCIES ON CACHE BOOL "Fetch Dawn dependencies" FORCE)
    set(DAWN_BUILD_SAMPLES OFF CACHE BOOL "Build Dawn samples" FORCE)
    set(DAWN_BUILD_NODE_BINDINGS OFF CACHE BOOL "Build Dawn Node bindings" FORCE)
    set(TINT_BUILD_TESTS OFF CACHE BOOL "Build Tint tests" FORCE)
    set(TINT_BUILD_SAMPLES OFF CACHE BOOL "Build Tint samples" FORCE)
    
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../external/dawn dawn_build)
    
    # Set Dawn include directories
    set(DAWN_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/dawn/include
        ${CMAKE_BINARY_DIR}/dawn_build/gen/include
    )
    
    # Set Dawn libraries
    set(DAWN_LIBRARIES
        webgpu_dawn
        dawn_native
        dawn_proc
    )
else()
    message(WARNING "Dawn not found at ${CMAKE_CURRENT_SOURCE_DIR}/../external/dawn")
    message(WARNING "Dawn examples will not be built. Please run: git submodule update --init --recursive")
    return()
endif()

# Find GLFW for windowing
find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    message(STATUS "GLFW not found, trying to use system package...")
    find_package(PkgConfig)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(GLFW glfw3)
    endif()
    
    if(NOT GLFW_FOUND)
        message(WARNING "GLFW not found. Dawn examples require GLFW for windowing.")
        message(WARNING "Please install GLFW: sudo apt-get install libglfw3-dev (Ubuntu/Debian)")
        return()
    endif()
endif()

# Triangle Demo - Basic Dawn usage
add_executable(dawn_triangle_demo triangle_demo.cpp)

target_link_libraries(dawn_triangle_demo
    ${DAWN_LIBRARIES}
    glfw
)

target_include_directories(dawn_triangle_demo PRIVATE
    ${DAWN_INCLUDE_DIRS}
)

# Shapes Demo - 3D shapes rendering
add_executable(dawn_shapes_demo shapes_demo.cpp)

target_link_libraries(dawn_shapes_demo
    ${DAWN_LIBRARIES}
    glfw
)

target_include_directories(dawn_shapes_demo PRIVATE
    ${DAWN_INCLUDE_DIRS}
)

# Set C++ standard
set_target_properties(dawn_triangle_demo dawn_shapes_demo
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

message(STATUS "Dawn examples configured successfully")
message(STATUS "  - Triangle Demo: Renders a simple red triangle")
message(STATUS "  - Shapes Demo: Renders 3D shapes (cube, pyramid) with rotation")

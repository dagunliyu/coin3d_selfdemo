cmake_minimum_required(VERSION 3.15)
project(coin3d_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories for all targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# For multi-config generators (Visual Studio, Xcode)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach()

# Configure Coin3D build options
set(COIN_BUILD_SHARED_LIBS ON CACHE BOOL "Build Coin3D as shared library")
set(COIN_BUILD_TESTS OFF CACHE BOOL "Skip Coin3D tests")
set(COIN_BUILD_DOCUMENTATION OFF CACHE BOOL "Skip Coin3D documentation")
set(COIN_BUILD_EXAMPLES OFF CACHE BOOL "Skip Coin3D builtin examples")

# Add local cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cMake")

# Add Coin3D as a subdirectory
message(STATUS "Building Coin3D from source in thirdparty/coin")
add_subdirectory(thirdparty/coin)
add_library(Coin::Coin ALIAS Coin)

# Configure SoQt build options
set(SOQT_BUILD_SHARED_LIBS ON CACHE BOOL "Build SoQt as shared library")
set(SOQT_BUILD_TESTS OFF CACHE BOOL "Skip SoQt tests")
set(SOQT_BUILD_DOCUMENTATION OFF CACHE BOOL "Skip SoQt documentation")
set(SOQT_BUILD_EXAMPLES OFF CACHE BOOL "Skip SoQt built-in examples")

# Add SoQt as a subdirectory
message(STATUS "Building SoQt from source in thirdparty/soqt")
add_subdirectory(thirdparty/soqt)
add_library(SoQt::SoQt ALIAS SoQt)

# Export Coin3D variables for examples to use
set(COIN_LIBRARY Coin CACHE INTERNAL "Coin3D library target")
set(COIN_LIBRARIES Coin CACHE INTERNAL "Coin3D library target")
set(COIN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/coin/include CACHE INTERNAL "Coin3D include directory")
set(COIN_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/thirdparty/coin/include CACHE INTERNAL "Coin3D include directory")

include(cMake)
add_subdirectory(cMake/cmakeHelper) # must have a CMakeLists

SetupOpenGL()

# Coin3D examples - organized by features
add_subdirectory(coin3d_examples)

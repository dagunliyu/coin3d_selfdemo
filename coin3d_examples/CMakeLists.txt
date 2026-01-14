# Coin3D Examples
# This directory contains various examples demonstrating Coin3D features
cmake_minimum_required(VERSION 3.15)

# Add cmake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cMake")

# Find Coin3D library
find_package(Coin REQUIRED)
find_package(SoQt REQUIRED)

# Set variables for subdirectories to use
set(COIN_LIBRARIES ${COIN_LIBRARY} PARENT_SCOPE)
set(SOQT_LIBRARIES ${SOQT_LIBRARY} PARENT_SCOPE)
set(COIN_INCLUDE_DIRS ${COIN_INCLUDE_DIR} PARENT_SCOPE)
set(SOQT_INCLUDE_DIRS ${SOQT_INCLUDE_DIR} PARENT_SCOPE)

# Make these available in this scope too
set(COIN_LIBRARIES ${COIN_LIBRARY})
set(SOQT_LIBRARIES ${SOQT_LIBRARY})
set(COIN_INCLUDE_DIRS ${COIN_INCLUDE_DIR})
set(SOQT_INCLUDE_DIRS ${SOQT_INCLUDE_DIR})

# Add subdirectories for different Coin3D features
add_subdirectory(basic_shapes)
add_subdirectory(scene_graph)
add_subdirectory(transformations)
add_subdirectory(materials)
add_subdirectory(lighting)
add_subdirectory(cameras)
add_subdirectory(text)
add_subdirectory(events)
add_subdirectory(file_io)
add_subdirectory(animation)

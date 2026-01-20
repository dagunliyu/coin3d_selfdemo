# Coin3D Examples
# This directory contains various examples demonstrating Coin3D features
cmake_minimum_required(VERSION 3.15)

# Add cmake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cMake")

# Use the Coin3D built from source
# COIN_LIBRARY, COIN_LIBRARIES, COIN_INCLUDE_DIR, COIN_INCLUDE_DIRS are already set by parent

# Use the SoQt built from source
# find_package(SoQt REQUIRED)
set(SOQT_LIBRARY SoQt::SoQt)

# Set variables for subdirectories to use
set(COIN_LIBRARIES ${COIN_LIBRARY} PARENT_SCOPE)
set(SOQT_LIBRARIES ${SOQT_LIBRARY} PARENT_SCOPE)
set(COIN_INCLUDE_DIRS ${COIN_INCLUDE_DIR} PARENT_SCOPE)

# Get SoQt directories for includes
get_target_property(SOQT_SOURCE_DIR SoQt SOURCE_DIR)
get_target_property(SOQT_BINARY_DIR SoQt BINARY_DIR)
set(SOQT_INCLUDE_DIRS 
    "${SOQT_SOURCE_DIR}/src"
    "${SOQT_BINARY_DIR}/src"
)
set(SOQT_INCLUDE_DIRS ${SOQT_INCLUDE_DIRS} PARENT_SCOPE)

# Make these available in this scope too
set(COIN_LIBRARIES ${COIN_LIBRARY})
set(SOQT_LIBRARIES ${SOQT_LIBRARY})
set(COIN_INCLUDE_DIRS ${COIN_INCLUDE_DIR})
# SOQT_INCLUDE_DIRS is already set above

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
add_subdirectory(rendering_pipeline)
add_subdirectory(gpu_data_transfer)

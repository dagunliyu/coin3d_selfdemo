# Basic Shapes Example - demonstrates Coin3D primitive shapes
cmake_minimum_required(VERSION 3.15)

# Create executable for basic shapes example
add_executable(basic_shapes_example main.cpp)

# Link Coin3D libraries
target_link_libraries(basic_shapes_example 
    ${COIN_LIBRARIES}
    # ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(basic_shapes_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    # ${SOQT_INCLUDE_DIRS}
)

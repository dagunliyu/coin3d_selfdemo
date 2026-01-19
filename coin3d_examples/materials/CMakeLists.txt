# Materials Example - demonstrates Coin3D materials and appearance
cmake_minimum_required(VERSION 3.15)

# Create executable for materials example
add_executable(materials_example main.cpp)

# Link Coin3D libraries
target_link_libraries(materials_example 
    ${COIN_LIBRARIES}
    ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(materials_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    # ${SOQT_INCLUDE_DIRS}
)

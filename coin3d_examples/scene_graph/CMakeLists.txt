# Scene Graph Example - demonstrates Coin3D scene graph manipulation
cmake_minimum_required(VERSION 3.15)

# Create executable for scene graph example
add_executable(scene_graph_example main.cpp)

# Link Coin3D libraries
target_link_libraries(scene_graph_example 
    ${COIN_LIBRARIES}
    ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(scene_graph_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    # ${SOQT_INCLUDE_DIRS}
)

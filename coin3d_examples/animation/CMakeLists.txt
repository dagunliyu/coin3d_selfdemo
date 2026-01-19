# Animation Example - demonstrates Coin3D animation
cmake_minimum_required(VERSION 3.15)

# Create executable for animation example
add_executable(animation_example main.cpp)

# Link Coin3D libraries
target_link_libraries(animation_example 
    ${COIN_LIBRARIES}
    # ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(animation_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    # ${SOQT_INCLUDE_DIRS}
)

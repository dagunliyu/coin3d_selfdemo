# Lighting Example - demonstrates Coin3D lighting
cmake_minimum_required(VERSION 3.15)

# Create executable for lighting example
add_executable(lighting_example main.cpp)

# Link Coin3D libraries
target_link_libraries(lighting_example 
    ${COIN_LIBRARIES}
    ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(lighting_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    ${SOQT_INCLUDE_DIRS}
)

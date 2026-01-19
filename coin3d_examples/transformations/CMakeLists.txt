# Transformations Example - demonstrates Coin3D transformations
cmake_minimum_required(VERSION 3.15)

# Create executable for transformations example
add_executable(transformations_example main.cpp)

# Link Coin3D libraries
target_link_libraries(transformations_example 
    ${COIN_LIBRARIES}
    
    
)

# Include directories
target_include_directories(transformations_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    # ${SOQT_INCLUDE_DIRS}
)

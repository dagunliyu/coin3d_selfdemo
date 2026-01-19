# Cameras Example - demonstrates Coin3D camera operations
cmake_minimum_required(VERSION 3.15)

# Create executable for cameras example
add_executable(cameras_example main.cpp)

# Link Coin3D libraries
target_link_libraries(cameras_example 
    ${COIN_LIBRARIES}
    # ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(cameras_example PRIVATE
    ${COIN_INCLUDE_DIRS}
   #  ${SOQT_INCLUDE_DIRS}
)

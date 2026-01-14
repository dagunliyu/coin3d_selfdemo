# File I/O Example - demonstrates Coin3D file reading and writing
cmake_minimum_required(VERSION 3.15)

# Create executable for file I/O example
add_executable(file_io_example main.cpp)

# Link Coin3D libraries
target_link_libraries(file_io_example 
    ${COIN_LIBRARIES}
    ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(file_io_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    ${SOQT_INCLUDE_DIRS}
)

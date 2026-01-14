# Text Example - demonstrates Coin3D text rendering
cmake_minimum_required(VERSION 3.15)

# Create executable for text example
add_executable(text_example main.cpp)

# Link Coin3D libraries
target_link_libraries(text_example 
    ${COIN_LIBRARIES}
    ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(text_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    ${SOQT_INCLUDE_DIRS}
)

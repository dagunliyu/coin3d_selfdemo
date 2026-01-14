# Events Example - demonstrates Coin3D event handling and interaction
cmake_minimum_required(VERSION 3.15)

# Create executable for events example
add_executable(events_example main.cpp)

# Link Coin3D libraries
target_link_libraries(events_example 
    ${COIN_LIBRARIES}
    ${SOQT_LIBRARIES}
)

# Include directories
target_include_directories(events_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    ${SOQT_INCLUDE_DIRS}
)

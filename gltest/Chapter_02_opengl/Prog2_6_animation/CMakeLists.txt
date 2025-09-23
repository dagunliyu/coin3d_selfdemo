
project(Prog2_6_animation)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    # ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${SOIL2_INCLUDE_DIR}
)

# 查找当前目录下所有源文件
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(Prog2_6_animation ${SOURCES})

target_link_libraries(Prog2_6_animation PRIVATE
    GLEW::GLEW    # ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${SOIL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

SET_BIN_DIR(Prog2_6_animation Prog2_6_animation)
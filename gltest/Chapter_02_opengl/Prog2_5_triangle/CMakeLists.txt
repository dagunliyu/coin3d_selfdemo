
project(Prog2_5_triangle)

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

add_executable(Prog2_5_triangle ${SOURCES})

target_link_libraries(Prog2_5_triangle PRIVATE
    GLEW::GLEW    # ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${SOIL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

message("BIN_DIR = ${BIN_DIR}")

file(GLOB GLSL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.glsl")
add_custom_command(
    TARGET Prog2_5_triangle 
    POST_BUILD                                      # 目标构建完成后执行
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${GLSL_FILES}
    ${BIN_DIR}
)

SET_BIN_DIR(Prog2_5_triangle Prog2_5_triangle)
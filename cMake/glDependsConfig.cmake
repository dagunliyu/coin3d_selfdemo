
# # glew
# set(GLEW_DIR ${SDK_DIR}/glew)
# set(GLEW_INCLUDE_DIR ${GLEW_DIR}/include)
# set(GLEW_LIBRARY_DIR ${GLEW_DIR}/lib)

# include_directories(${GLEW_INCLUDE_DIR})
# link_directories(${GLEW_LIBRARY_DIR})

# set(GLEW_LIBRARIES
#     glew32.lib
#     glew32s.lib)

# glfw
set(GLFW_DIR "${SDK_DIR}/glfw")
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include)
set(GLFW_LIBRARY_DIR ${GLFW_DIR}/lib)

include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

set(GLFW_LIBRARIES
    glfw3.lib)

# glm
set(GLM_DIR "${SDK_DIR}/glm")
set(GLM_INCLUDE_DIR ${SDK_DIR}) # use glm/common.hpp to distinguish

# soil2
set(SOIL2_DIR "${SDK_DIR}/soil2")
set(SOIL2_INCLUDE_DIR ${SOIL2_DIR}/include)
set(SOIL2_LIBRARY_DIR ${SOIL2_DIR}/lib)

include_directories(${SOIL2_INCLUDE_DIR})
link_directories(${SOIL2_LIBRARY_DIR})

set(SOIL2_LIBRARIES
    soil2.lib
    soil2-debug.lib)
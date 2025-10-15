##########################################################
# glew
set(GLEW_DIR ${SDK_DIR}/glew CACHE PATH "")
set(GLEW_INCLUDE_DIR ${GLEW_DIR}/include CACHE PATH "")
set(GLEW_LIBRARY_DIR ${GLEW_DIR}/lib CACHE PATH "")
set(GLEW_LIBRARIES
    ${GLEW_LIBRARY_DIR}/glew32.lib
    ${GLEW_LIBRARY_DIR}/glew32s.lib)

add_library(GLEW::GLEW SHARED IMPORTED GLOBAL)
set_target_properties(GLEW::GLEW PROPERTIES 
    IMPORTED_LOCATION "${GLEW_DIR}/bin//glew32.dll"
    IMPORTED_IMPLIB "${GLEW_LIBRARY_DIR}/glew32.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}"
)

##########################################################
# glfw
set(GLFW_DIR "${SDK_DIR}/glfw")
set(GLFW_INCLUDE_DIR ${GLFW_DIR}/include)
set(GLFW_LIBRARY_DIR ${GLFW_DIR}/lib)

include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIR})

set(GLFW_LIBRARIES
    glfw3.lib)

##########################################################
# glm
set(GLM_DIR "${SDK_DIR}/glm")
set(GLM_INCLUDE_DIR ${SDK_DIR}) # use glm/common.hpp to distinguish

##########################################################
# soil2
set(SOIL2_DIR "${SDK_DIR}/soil2")
set(SOIL2_INCLUDE_DIR ${SOIL2_DIR}/include)
set(SOIL2_LIBRARY_DIR ${SOIL2_DIR}/lib)

# 注意：include_directories作用域向下传递/
include_directories(${SOIL2_INCLUDE_DIR})
link_directories(${SOIL2_LIBRARY_DIR})

set(SOIL2_LIBRARIES
    soil2.lib
    soil2-debug.lib)
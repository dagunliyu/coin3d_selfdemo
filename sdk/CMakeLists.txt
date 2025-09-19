


# 由MATCHES改为STREQUAL? 无提示
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(SDK_DIR "${CMAKE_SOURCE_DIR}/sdk/Windows" CACHE PATH "Directory of SDK")
    add_subdirectory(Windows)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "aarch64")
        set(SDK_DIR "${CMAKE_SOURCE_DIR}/sdk/Linux_Arm" CACHE PATH "Directory of SDK")
        add_subdirectory(Linux_Arm)
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(SDK_DIR "${CMAKE_SOURCE_DIR}/sdk/Linux_x86" CACHE PATH "Directory of SDK")
        add_subdirectory(Linux_x86)
    endif()
endif()


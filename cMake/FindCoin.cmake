# FindCoin.cmake - Find Coin3D library
# This module defines:
#  COIN_FOUND - System has Coin3D
#  COIN_INCLUDE_DIR - The Coin3D include directory
#  COIN_LIBRARY - The Coin3D library
#  COIN_VERSION - The version of Coin3D found

if(TARGET Coin)
    set(COIN_FOUND TRUE)
    set(COIN_LIBRARY Coin)
    set(COIN_LIBRARIES Coin)
    get_target_property(COIN_SOURCE_DIR Coin SOURCE_DIR)
    get_target_property(COIN_BINARY_DIR Coin BINARY_DIR)
    set(COIN_INCLUDE_DIR "${COIN_SOURCE_DIR}/include" "${COIN_BINARY_DIR}/include")
    set(COIN_INCLUDE_DIRS ${COIN_INCLUDE_DIR})
    if(NOT TARGET Coin::Coin)
        add_library(Coin::Coin ALIAS Coin)
    endif()
    return()
endif()

find_path(COIN_INCLUDE_DIR 
    NAMES Inventor/So.h
    PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        $ENV{COINDIR}/include
    PATH_SUFFIXES coin4 coin3 coin2
)

find_library(COIN_LIBRARY
    NAMES Coin coin4 coin3 coin2
    PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        $ENV{COINDIR}/lib
    PATH_SUFFIXES x86_64-linux-gnu
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Coin
    REQUIRED_VARS COIN_LIBRARY COIN_INCLUDE_DIR
)

mark_as_advanced(COIN_INCLUDE_DIR COIN_LIBRARY)

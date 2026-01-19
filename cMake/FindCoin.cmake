# FindCoin.cmake - Find Coin3D library
# This module defines:
#  COIN_FOUND - System has Coin3D
#  COIN_INCLUDE_DIR - The Coin3D include directory
#  COIN_LIBRARY - The Coin3D library
#  COIN_VERSION - The version of Coin3D found

find_path(COIN_INCLUDE_DIR 
    NAMES Inventor/So.h
    PATHS
        ${CMAKE_SOURCE_DIR}/external/coin/include
        /usr/include
        /usr/local/include
        /opt/local/include
        $ENV{COINDIR}/include
        "C:/Program Files/Coin3D/include"
    PATH_SUFFIXES coin4 coin3 coin2
)

find_library(COIN_LIBRARY
    NAMES Coin Coin4 coin4 coin3 coin2
    PATHS
        ${CMAKE_BINARY_DIR}/external/coin
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        $ENV{COINDIR}/lib
        "C:/Program Files/Coin3D/lib"
    PATH_SUFFIXES x86_64-linux-gnu Release Debug
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Coin
    REQUIRED_VARS COIN_LIBRARY COIN_INCLUDE_DIR
)

mark_as_advanced(COIN_INCLUDE_DIR COIN_LIBRARY)

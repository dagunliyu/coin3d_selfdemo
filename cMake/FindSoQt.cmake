# FindSoQt.cmake - Find SoQt library
# This module defines:
#  SOQT_FOUND - System has SoQt
#  SOQT_INCLUDE_DIR - The SoQt include directory
#  SOQT_LIBRARY - The SoQt library
#  SOQT_VERSION - The version of SoQt found

find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL QUIET)
if(NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL QUIET)
endif()

find_path(SOQT_INCLUDE_DIR
    NAMES Inventor/Qt/SoQt.h
    PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        $ENV{SOQTDIR}/include
    PATH_SUFFIXES SoQt
)

find_library(SOQT_LIBRARY
    NAMES SoQt soqt
    PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        $ENV{SOQTDIR}/lib
    PATH_SUFFIXES x86_64-linux-gnu
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SoQt
    REQUIRED_VARS SOQT_LIBRARY SOQT_INCLUDE_DIR
)

mark_as_advanced(SOQT_INCLUDE_DIR SOQT_LIBRARY)

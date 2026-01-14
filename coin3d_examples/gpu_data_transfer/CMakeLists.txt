cmake_minimum_required(VERSION 3.15)

project(gpu_data_transfer_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找必需的包
find_package(Coin REQUIRED)
find_package(SoQt REQUIRED)

# Qt5 或 Qt6
find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL QUIET)
if (NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets REQUIRED)
endif()

# 源文件
set(SOURCES main.cpp)

# 创建可执行文件
add_executable(gpu_data_transfer_example ${SOURCES})

# 链接库
if (Qt5_FOUND)
    target_link_libraries(gpu_data_transfer_example
        Coin::Coin
        SoQt::SoQt
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::OpenGL
    )
else()
    target_link_libraries(gpu_data_transfer_example
        Coin::Coin
        SoQt::SoQt
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
    )
endif()

# 包含目录
target_include_directories(gpu_data_transfer_example PRIVATE
    ${COIN_INCLUDE_DIRS}
    ${SOQT_INCLUDE_DIRS}
)

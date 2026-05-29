cmake_minimum_required(VERSION 3.10)
project(DeepSeekChatBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 Qt5 的自动 MOC、UIC、RCC 处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 找到 libcurl
find_package(CURL REQUIRED)

# 找到 Qt5
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

# 添加包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 创建命令行版本的可执行文件
add_executable(chatbot_cli src/chatbot.cpp)
target_link_libraries(chatbot_cli PRIVATE CURL::libcurl)

# 创建 Qt5 GUI 版本的可执行文件
add_executable(chatbot_gui 
    src/gui/main_gui.cpp
    src/gui/chatbot_widget.cpp
    src/gui/chatbot_widget.hpp
)

target_link_libraries(chatbot_gui PRIVATE 
    Qt5::Core 
    Qt5::Gui 
    Qt5::Widgets 
    Qt5::Network
    CURL::libcurl
)

# 如果找不到依赖库，给出有用的提示
if(NOT CURL_FOUND)
    message(FATAL_ERROR "libcurl not found. Please install it using:\n"
            "  Ubuntu/Debian: sudo apt-get install libcurl4-openssl-dev\n"
            "  macOS: brew install curl\n"
            "  Windows (vcpkg): vcpkg install curl:x64-windows")
endif()

if(NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found. Please install it using:\n"
            "  Ubuntu/Debian: sudo apt-get install qt5-qmake qtbase5-dev\n"
            "  macOS: brew install qt5\n"
            "  Windows: Download from https://www.qt.io/download")
endif()

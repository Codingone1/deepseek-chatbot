cmake_minimum_required(VERSION 3.10)
project(DeepSeekChatBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找到 libcurl
find_package(CURL REQUIRED)

# 创建可执行文件
add_executable(chatbot src/chatbot.cpp)

# 链接 libcurl
target_link_libraries(chatbot PRIVATE CURL::libcurl)

# 如果找不到 CURL，给出有用的提示
if(NOT CURL_FOUND)
    message(FATAL_ERROR "libcurl not found. Please install it using:\n"
            "  Ubuntu/Debian: sudo apt-get install libcurl4-openssl-dev\n"
            "  macOS: brew install curl\n"
            "  Windows (vcpkg): vcpkg install curl:x64-windows")
endif()

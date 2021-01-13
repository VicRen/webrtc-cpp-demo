cmake_minimum_required(VERSION 3.17)
project(webrtc_cpp_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT_DIR}/$ENV{QT_VERSION}/clang_64/lib/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

add_executable(webrtc_cpp_demo main.cpp)
target_link_libraries(webrtc_cpp_demo Qt5::Widgets)
cmake_minimum_required(VERSION 3.17)
project(webrtc_cpp_demo)

# cmake param should set WEBRTC_HEADER_PATH/WEBRTC_LIB_PATH
if (NOT WEBRTC_INCLUDE_PATH)
    message(FATAL_ERROR "WEBRTC_INCLUDE_PATH not provided")
else()
    message(STATUS "WEBRTC_INCLUDE_PATH = " ${WEBRTC_INCLUDE_PATH})
endif()

if (NOT WEBRTC_LIB_PATH)
    message(FATAL_ERROR "WEBRTC_LIB_PATH not provided")
else()
    message(STATUS "WEBRTC_LIB_PATH = " ${WEBRTC_LIB_PATH})
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT_DIR}/$ENV{QT_VERSION}/clang_64/lib/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

add_subdirectory(webrtc)

add_executable(webrtc_cpp_demo main.cpp settings.cpp settings.h settings.ui)

add_definitions(-DQT_NO_KEYWORDS)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${WEBRTC_INCLUDE_PATH}
        ${WEBRTC_INCLUDE_PATH}/third_party/abseil-cpp
        ${PROJECT_SOURCE_DIR}/webrtc
        )
target_link_libraries(webrtc_cpp_demo WebRTC_lib Qt5::Widgets)
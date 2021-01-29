project(WebRTC_lib)

set(
        SOURCE_FILES
        ThreadManager.cpp
        Singleton.h StatsReporter.cpp StatsReporter.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set_source_files_properties(${SOURCE_FILES}
        PROPERTIES COMPILE_FLAGS -Wall -Wextra -Wpedantic)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

find_library(FOUNDATION Foundation)
find_library(CORE_FOUNDATION CoreFoundation)
find_library(CORE_SERVICES CoreServices)
find_library(CORE_AUDIO_FOUNDATION CoreAudio)
find_library(AUDIO_UNIT AudioUnit)
find_library(AUDIO_TOOLBOX AudioToolbox)
find_library(CORE_GRAPHICS CoreGraphics)
find_library(COCOA Cocoa)

set(EXTRA_LIBS ${FOUNDATION} ${CORE_FOUNDATION} ${CORE_SERVICES} ${CORE_AUDIO_FOUNDATION} ${AUDIO_UNIT} ${AUDIO_TOOLBOX} ${CORE_GRAPHICS} ${COCOA})

target_include_directories(${PROJECT_NAME} PRIVATE
        ${WEBRTC_INCLUDE_PATH}
        ${WEBRTC_INCLUDE_PATH}/third_party/abseil-cpp
        )

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${WEBRTC_LIB_PATH}/libwebrtc${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${EXTRA_LIBS}
        )

# Compile definitions for libwebrtc.
target_compile_definitions(${PROJECT_NAME} PUBLIC
        $<$<NOT:$<PLATFORM_ID:Windows>>:WEBRTC_POSIX>
        $<$<PLATFORM_ID:Windows>:WEBRTC_WIN WIN32_LEAN_AND_MEAN>
        $<$<PLATFORM_ID:Darwin>:WEBRTC_MAC>
        )
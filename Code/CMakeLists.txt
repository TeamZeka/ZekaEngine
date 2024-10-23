cmake_minimum_required(VERSION 3.6.0)
project("ZekaEngineProject")

if (ANDROID)

add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue)

endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(THIRDPARTY_PATH ../ThirdParty)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${THIRDPARTY_PATH}/stb
  ${THIRDPARTY_PATH}/freetype
  ${THIRDPARTY_PATH}/OpenAL
  ${THIRDPARTY_PATH}/minimp3
)

if (WIN32)

add_definitions(-DZK_PLATFORM_WINDOWS)

elseif (ANDROID)

add_definitions(-DZK_PLATFORM_ANDROID -DZK_PLATFORM_POSIX)

endif()

add_subdirectory(ZekaEngine)
add_subdirectory(ZekaApplication)

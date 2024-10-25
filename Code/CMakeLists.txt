cmake_minimum_required(VERSION 3.6.0)
project("ZekaEngineProject")

if (ANDROID)

add_library(native_app_glue STATIC
  ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
  ${ANDROID_NDK}/sources/android/native_app_glue)

endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(THIRDPARTY_PATH ThirdParty)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${THIRDPARTY_PATH}/stb
  ${THIRDPARTY_PATH}/freetype/include
  ${THIRDPARTY_PATH}/openal-soft/include
  ${THIRDPARTY_PATH}/minimp3
)

if (WIN32)

add_definitions(-DZK_PLATFORM_WINDOWS)

elseif (ANDROID)

add_definitions(-DZK_PLATFORM_ANDROID -DZK_PLATFORM_POSIX)

endif()

function(get_all_targets _result _dir)
  get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
  foreach(_subdir IN LISTS _subdirs)
    get_all_targets(${_result} "${_subdir}")
  endforeach()
  get_property(_sub_targets DIRECTORY "${_dir}" PROPERTY BUILDSYSTEM_TARGETS)
  set(${_result} ${${_result}} ${_sub_targets} PARENT_SCOPE)
endfunction()

function(add_subdirectory_with_folder _folder_name _folder)
  add_subdirectory(${_folder} ${ARGN})
  get_all_targets(_targets "${_folder}")
  foreach(_target IN LISTS _targets)
    set_target_properties(
            ${_target}
            PROPERTIES FOLDER "${_folder_name}"
    )
  endforeach()
endfunction()

add_subdirectory_with_folder("ThirdParty" ${THIRDPARTY_PATH}/openal-soft)
add_subdirectory_with_folder("ThirdParty" ${THIRDPARTY_PATH}/freetype)

add_subdirectory(ZekaEngine)
add_subdirectory(ZekaApplication)

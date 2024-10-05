# ZekaEngine CMakeLists.txt

if (ANDROID)

find_library(log-lib log)

endif()

set(ZekaEngine_SOURCES)

file(GLOB _ZekaEngine_SOURCES
  "*.cpp"
  "*.h"
)

list(APPEND ZekaEngine_SOURCES ${_ZekaEngine_SOURCES})

list(APPEND ZekaEngine_SOURCES "OpenGL/IncludeOpenGLHeaders.h")
list(APPEND ZekaEngine_SOURCES "OpenGL/RHI_OpenGL.h")
list(APPEND ZekaEngine_SOURCES "OpenGL/RHI_OpenGL.cpp")

set(OpenGLLoader_SOURCES
  "OpenGL/OpenGLFunctions.h"
  "OpenGL/OpenGLLoader.h"
  "OpenGL/OpenGLLoader.cpp"
  "OpenGL/glcorearb.h"
  "OpenGL/khrplatform.h"
)

if (WIN32)

file(GLOB Windows_ZekaEngine_SOURCES
  "Windows/*.cpp"
  "Windows/*.h"
)

list(APPEND ZekaEngine_SOURCES ${Windows_ZekaEngine_SOURCES})
list(APPEND ZekaEngine_SOURCES ${OpenGLLoader_SOURCES})

elseif (ANDROID)

file(GLOB Android_ZekaEngine_SOURCES
  "Android/*.cpp"
  "Android/*.h"
  "Posix/*.cpp"
  "Posix/*.h"
)

list(APPEND ZekaEngine_SOURCES ${Android_ZekaEngine_SOURCES})

endif()

add_library(ZekaEngine
  ${ZekaEngine_SOURCES}
)

if (ANDROID)

target_link_libraries(ZekaEngine

  android
  native_app_glue
  ${log-lib}
  EGL
  GLESv3)

elseif (WIN32)

target_link_libraries(ZekaEngine

  opengl32)

endif()

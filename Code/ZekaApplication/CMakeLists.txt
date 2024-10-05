# ZekaApplication CMakeLists.txt

file(GLOB ZekaApplication_SOURCES
  "*.cpp"
  "*.h"
)

if (ANDROID)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
add_library(ZekaApplication SHARED ${ZekaApplication_SOURCES})

else()

if (WIN32)
add_executable(ZekaApplication WIN32 ${ZekaApplication_SOURCES})
else()
add_executable(ZekaApplication ${ZekaApplication_SOURCES})
endif()


endif()

target_link_libraries(ZekaApplication PRIVATE
  ZekaEngine
)

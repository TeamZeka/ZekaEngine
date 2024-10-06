#include "ZekaEngine/Platform.h"

#include <android/log.h>
#include <EGL/egl.h>

ZK_NAMESPACE_BEGIN

void Platform::Log(LogLevel level, const char* msg)
{
  int prio = 0;
  switch(level)
  {
  case LogLevel::Error: prio = ANDROID_LOG_ERROR; break;
  case LogLevel::Information: prio = ANDROID_LOG_INFO; break;
  case LogLevel::Warning: prio = ANDROID_LOG_WARN; break;
  }

  __android_log_print(prio, "ZekaEngine", "%s", msg);
}

void* Platform::GetGLProcAddress(const char* name)
{
  return (void*)eglGetProcAddress(name);
}

ZK_NAMESPACE_END

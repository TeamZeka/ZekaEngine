#ifndef _H_PLATFORM
#define _H_PLATFORM

#include "HelperDefines.h"

ZK_NAMESPACE_BEGIN

class Platform
{
public:
  enum class LogLevel : uint32
  {
    Error = 0,
    Information,
    Warning
  };

public:
  static void Log(LogLevel level, const char* msg);
  static uint64 GetFrequency();
  static uint64 GetCounter();
  static void* LoadModule(const char* name);
  static void FreeLibrary(void* lib);
  static void* GetProcAddress(void* lib, const char* name);
  static void* GetGLProcAddress(const char* name);
};

ZK_NAMESPACE_END

#endif

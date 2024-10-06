#include "ZekaEngine/Platform.h"

#include <time.h>
#include <dlfcn.h>

ZK_NAMESPACE_BEGIN

uint64 Platform::GetFrequency()
{
  return 1000000;
}

uint64 Platform::GetCounter()
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  return static_cast<uint64>(static_cast<uint64>(ts.tv_sec) * 1000000ULL + static_cast<uint64>(ts.tv_nsec) / 1000ULL);
}

void* Platform::LoadModule(const char* name)
{
  return dlopen(name, RTLD_LOCAL | RTLD_LAZY);
}

void Platform::FreeLibrary(void* lib)
{
  if (lib != NULL)
  {
    dlclose(lib);
  }
}

void* Platform::GetProcAddress(void* lib, const char* name)
{
    return dlsym(lib, name);
}

ZK_NAMESPACE_END

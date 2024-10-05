#include "ZekaEngine/Platform.h"
#include "IncludeWindowsHeaders.h"

ZK_NAMESPACE_BEGIN

void Platform::Log(LogLevel level, const char* msg)
{
  switch (level)
  {
  case Zeka::Platform::LogLevel::Error: OutputDebugStringA("[Error] "); break;
  case Zeka::Platform::LogLevel::Information: OutputDebugStringA("[Information] "); break;
  case Zeka::Platform::LogLevel::Warning: OutputDebugStringA("[Warning] "); break;
  }

  OutputDebugStringA(msg);
  OutputDebugStringA("\n");
}

uint64 Platform::GetFrequency()
{
  LARGE_INTEGER tmp;
  QueryPerformanceFrequency(&tmp);
  return tmp.QuadPart;
}

uint64 Platform::GetCounter()
{
  LARGE_INTEGER tmp;
  QueryPerformanceCounter(&tmp);
  return tmp.QuadPart;
}

void* Platform::LoadModule(const char* name)
{
  return (void*)LoadLibraryA(name);
}

void Platform::FreeLibrary(void* lib)
{
  ::FreeLibrary((HMODULE)lib);
}

void* Platform::GetProcAddress(void* lib, const char* name)
{
  return ::GetProcAddress((HMODULE)lib, name);
}

void* Platform::GetGLProcAddress(const char* name)
{
  return wglGetProcAddress(name);
}

ZK_NAMESPACE_END

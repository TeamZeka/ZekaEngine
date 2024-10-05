#ifndef _H_INCLUDE_WINDOWS_HEADERS
#define _H_INCLUDE_WINDOWS_HEADERS

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

// addons

inline WCHAR* CreateWideString(const char* str) 
{
  int count = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
  WCHAR* buffer = new WCHAR[count];

  MultiByteToWideChar(CP_UTF8, 0, str, -1, buffer, count);
  return buffer;
}

inline char* CreateUTF8String(const WCHAR* str) 
{
  int count = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
  char* buffer = new char[count];

  WideCharToMultiByte(CP_UTF8, 0, str, -1, buffer, count, NULL, NULL);
  return buffer;
}

#endif

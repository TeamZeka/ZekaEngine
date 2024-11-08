#ifndef _H_HELPER_DEFINES
#define _H_HELPER_DEFINES

#define ZK_NAMESPACE_BEGIN namespace Zeka {
#define ZK_NAMESPACE_END   }

ZK_NAMESPACE_BEGIN

template<typename T>
inline void Swap(T&& x, T&& y)
{
  T tmp = x;
  x = y;
  y = tmp;
}

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef long long int64;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;

#ifdef ZK_PLATFORM_ANDROID
#define ZK_OPENGLES
#if GL_ES_VERSION_3_0
#define ZK_OPENGLES_3_0
#endif
#endif

ZK_NAMESPACE_END

#endif

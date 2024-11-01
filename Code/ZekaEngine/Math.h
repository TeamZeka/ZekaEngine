#ifndef _H_MATH
#define _H_MATH

#include "HelperDefines.h"

#include <cmath>
#include <limits>

#include <stdint.h>
#include <limits>

#define ZK_INF							std::numeric_limits<float>::infinity()
#define ZK_MIN							std::numeric_limits<float>::min()
#define ZK_MAX							std::numeric_limits<float>::max()
#define ZK_PI							3.14159265358979323846
#define ZK_DEG2RAD				  ZK_PI / 180.0f
#define ZK_RAD2DEG					180.0f / ZK_PI
#define ZK_ZERO_TOLERANCE	1e-6f
#define ZK_ZERO_TOLERANCED 1e-16
#define ZK_EPSILON					0.000001f

ZK_NAMESPACE_BEGIN

namespace Math
{

  template<typename T>
  inline T Square(T x) { return x * x; }
  template<typename T>
  inline T Cube(T x) { return x * x * x; }
  template<typename T>
  inline T Radians(T x) { return x * static_cast<T>(ZK_DEG2RAD); }
  template<typename T>
  inline T Degrees(T x) { return x * static_cast<T>(ZK_RAD2DEG); }
  template<typename T>
  inline T Abs(T x) { return x < static_cast<T>(0) ? -x : x; }
  template<typename T>
  inline T Min(T x, T y) { return x < y ? y : x; }
  template<typename T>
  inline T Max(T x, T y) { return x > y ? y : x; }
  template<typename T>
  inline T Clamp(T x, T y, T z) { return x < y ? y : x > z ? z : x; }

  inline bool IsZero(float x) { return abs(x) < ZK_ZERO_TOLERANCE; }
  inline bool IsOne(float x) { return IsZero(x - 1.0f); }
  inline bool IsZero(int32_t x) { return x == 0; }
  inline bool IsOne(int32_t x) { return x == 1; }

  inline int32 TruncToInt(float val) { return int32(val); }
  inline int32 FloorToInt(float val) { return TruncToInt(floorf(val)); }
  inline int32 RoundToInt(float val) { return FloorToInt(val + 0.5f); }

  inline bool IsNaN(double val)
  {
#ifdef _MSC_VER
    return _isnan(val);
#elif defined(__GNUC__) && __GNUC__ < 6
    union {
      uint64_t u;
      double f;
    } ieee754;
    ieee754.f = val;
    // (unsigned)(0x7ff0000000000001 >> 32) : 0x7ff00000
    return ((((unsigned)(ieee754.u >> 32) & 0x7fffffff) + ((unsigned)ieee754.u != 0)) > 0x7ff00000);
#else
    return isnan(val);
#endif
  }

  inline bool IsNaN(float val)
  {
#ifdef _MSC_VER
    return _isnan(val);
#elif defined(__GNUC__) && __GNUC__ < 6
    union {
      uint32_t u;
      float f;
    } ieee754;
    ieee754.f = val;
    return ((ieee754.u & 0x7fffffff) > 0x7f800000);
#else
    return isnan(val);
#endif
  }

  inline bool IsInfinite(double val)
  {
#ifdef _MSC_VER
    return !_finite(val);
#elif defined(__GNUC__) && __GNUC__ < 6
    union {
      uint64_t u;
      double f;
    } ieee754;
    ieee754.f = val;
    return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 &&
    	((unsigned)ieee754.u == 0);
#else
    return isinf(val);
#endif
  }

  inline bool IsInfinite(float val)
  {
#ifdef _MSC_VER
    return !_finite(val);
#elif defined(__GNUC__) && __GNUC__ < 6
    union {
      uint32_t u;
      float f;
    } ieee754;
    ieee754.f = val;
    return (ieee754.u & 0x7fffffff) == 0x7f800000;
#else
    return isinf(val);
#endif
  }

  inline int Rand()
  {
    return rand();
  }

  inline int RandRange(int max)
  {
    return rand() % max;
  }

  inline int RandRange(int min, int max)
  {
    return min + rand() % (max - min);
  }

  inline float Randf()
  {
    return float(rand()) / float(RAND_MAX);
  }

  inline float RandRangef(float max)
  {
    return Randf() * max;
  }

  inline float RandRangef(float min, float max)
  {
    return min + Randf() * (max - min);
  }
}


ZK_NAMESPACE_END

#endif

#include "ZekaEngine/Platform.h"

#include <time.h>

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

ZK_NAMESPACE_END

#include "Time.h"

ZK_NAMESPACE_BEGIN

double Time::s_InvFrequency = 0;

void Time::Initialize()
{
  uint64 freq = Platform::GetFrequency();

  s_InvFrequency = 1.0 / double(freq);
}

double Time::Now()
{
  return double(Platform::GetCounter()) * s_InvFrequency;
}

ZK_NAMESPACE_END

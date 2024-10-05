#include "Platform.h"

ZK_NAMESPACE_BEGIN

class Time
{
public:
  static void Initialize();
  static double Now();
private:
  static double s_InvFrequency;
};

ZK_NAMESPACE_END

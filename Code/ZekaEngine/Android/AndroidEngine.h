#ifndef _H_ANDROID_ENGINE
#define _H_ANDROID_ENGINE

#include "ZekaEngine/Engine.h"

#include <android_native_app_glue.h>

ZK_NAMESPACE_BEGIN

class AndroidEngine : public Engine
{
public:
  AndroidEngine();
  ~AndroidEngine();

  void SetNativeApplication(android_app* app);
  android_app* GetNativeApplication();
private:
  android_app* m_NativeApplication = nullptr;
};

ZK_NAMESPACE_END

#endif

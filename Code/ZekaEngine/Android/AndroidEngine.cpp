#include "AndroidEngine.h"

ZK_NAMESPACE_BEGIN

AndroidEngine::AndroidEngine()
{
}

AndroidEngine::~AndroidEngine()
{
}

void AndroidEngine::SetNativeApplication(android_app* app)
{
  m_NativeApplication = app;
}

android_app* AndroidEngine::GetNativeApplication()
{
  return m_NativeApplication;
}

ZK_NAMESPACE_END

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

AAssetManager* AndroidEngine::GetAssetManager()
{
  return m_NativeApplication->activity->assetManager;
}

ZK_NAMESPACE_END

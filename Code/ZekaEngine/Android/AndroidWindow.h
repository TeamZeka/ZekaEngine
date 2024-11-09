#ifndef _H_ANDROID_WINDOW
#define _H_ANDROID_WINDOW

#include "ZekaEngine/Window.h"

#include <android_native_app_glue.h>
#include <android/native_window.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

ZK_NAMESPACE_BEGIN

class AndroidWindow : public Window
{
public:
  AndroidWindow(const char* name, EventHandler& handler);
  ~AndroidWindow();

  void HandleCmd(int32_t cmd);
  int32_t HandleInput(AInputEvent* inputEvent);

  void PollEvents() override;
  void* GetHandle() const override;
  bool DestroyRequested() const override;
  void SetFullscreen(bool fullscreen) override;
private:
  android_app* m_pApp;

  bool m_IsInitialized = false;
};

ZK_NAMESPACE_END

#endif

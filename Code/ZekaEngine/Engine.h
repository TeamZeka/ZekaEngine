#ifndef _H_ENGINE
#define _H_ENGINE

#include "Application.h"
#include "Window.h"
#include "RHIBase.h"

ZK_NAMESPACE_BEGIN

class Engine
{
public:
  Engine();
  ~Engine();

  void SetApplication(Application* app);
  Application* GetApplication();
  Window* GetWindow();
  RenderDevice* GetRenderDevice();

  void Run();

  static Engine* Get();
protected:
  Application* m_Application;
  Window* m_Window;
  EventHandler m_EventHandler;
  RenderDevice* m_RenderDevice;

  struct
  {
    double Now = 0;
    double LastTime = 0;
    float DeltaTime = 0;
  } m_Timer;
private:
  static Engine* s_Engine;
};

ZK_NAMESPACE_END

#endif

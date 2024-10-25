#ifndef _H_APPLICATION
#define _H_APPLICATION

#include "HelperDefines.h"
#include "Event.h"

ZK_NAMESPACE_BEGIN

class Application;

struct ApplicationCreateParams
{
  const char* Name;
  int Width;
  int Height;
  bool WindowResizable;
};

class Application
{
public:
  Application() {}
  ~Application() {}

  virtual void OnInitialize() {}
  virtual void OnUpdate(float dt) {}
  virtual void OnEvent(Event& event) {}

  const ApplicationCreateParams& GetParams() const { return m_Params; }
protected:
  ApplicationCreateParams m_Params;
};

extern Application* CreateApplication();

ZK_NAMESPACE_END

#endif

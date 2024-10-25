#ifndef _H_STATE
#define _H_STATE

#include "Application.h"

ZK_NAMESPACE_BEGIN

class State
{
public:
  State(Application* root) : m_Root(root) {}
  ~State() {}

  virtual void OnInitialize() {}
  virtual void OnUpdate(float dt) {}
  virtual void OnEvent(Event& event) {}
protected:
  Application* m_Root;
};

class StateManager
{
public:
  StateManager()
    : m_State(nullptr)
  {
  }

  ~StateManager()
  {
  }

  State* GetState()
  {
    return m_State;
  }

  void SetState(State* state)
  {
    if (!state)
    {
      return;
    }

    state->OnInitialize();
    m_State = state;
  }

  bool IsStateValid() const
  {
    return m_State != nullptr;
  }

  void OnInitialize()
  {
  }

  void OnUpdate(float dt)
  {
    if (m_State)
    {
      m_State->OnUpdate(dt);
    }
  }

  void OnEvent(Event& event)
  {
    if (m_State)
    {
      m_State->OnEvent(event);
    }
  }

private:
  State* m_State = nullptr;
};

ZK_NAMESPACE_END

#endif

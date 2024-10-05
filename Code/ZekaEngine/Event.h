#ifndef _H_EVENT
#define _H_EVENT

#include "HelperDefines.h"
#include "KeyCode.h"

#include <functional>
#include <utility>

ZK_NAMESPACE_BEGIN

enum class EventType : uint32
{
  WindowClose = 0,
  WindowSize,
  KeyDown,
  KeyUp,
  MouseButtonDown,
  MouseButtonUp,
  TouchDown,
  TouchUp,
  TouchMove
};

struct Event
{
  Event(EventType type)
    : Type(type)
  {
  }

  EventType Type;
};

template<class T>
inline T& GetEvent(Event& event)
{
  return static_cast<T&>(event);
}

struct WindowCloseEvent : public Event
{
  static EventType GetType()
  {
    return EventType::WindowClose;
  }

  WindowCloseEvent()
    : Event(EventType::WindowClose)
  {
  }
};

struct WindowSizeEvent : public Event
{
  static EventType GetType()
  {
    return EventType::WindowSize;
  }

  WindowSizeEvent(int width, int height)
    : Event(EventType::WindowSize)
    , Width(width)
    , Height(height)
  {
  }

  int Width;
  int Height;
};

struct KeyDownEvent : public Event
{
  static EventType GetType()
  {
    return EventType::KeyDown;
  }

  KeyDownEvent(KeyCode key)
    : Event(EventType::KeyDown)
    , Key(key)
  {
  }

  KeyCode Key;
};

struct KeyUpEvent : public Event
{
  static EventType GetType()
  {
    return EventType::KeyUp;
  }

  KeyUpEvent(KeyCode key)
    : Event(EventType::KeyUp)
    , Key(key)
  {
  }

  KeyCode Key;
};

struct MouseButtonDownEvent : public Event
{
  static EventType GetType()
  {
    return EventType::MouseButtonDown;
  }

  MouseButtonDownEvent(MouseButton button)
    : Event(EventType::MouseButtonDown)
    , Button(button)
  {
  }

  MouseButton Button;
};

struct MouseButtonUpEvent : public Event
{
  static EventType GetType()
  {
    return EventType::MouseButtonUp;
  }

  MouseButtonUpEvent(MouseButton button)
    : Event(EventType::MouseButtonUp)
    , Button(button)
  {
  }

  MouseButton Button;
};

struct TouchDownEvent : public Event
{
  static EventType GetType()
  {
    return EventType::TouchDown;
  }

  TouchDownEvent(float x, float y, int32 pointerID)
    : Event(EventType::TouchDown)
    , X(x)
    , Y(y)
    , PointerID(pointerID)
  {
  }

  float X;
  float Y;
  int32 PointerID;
};

struct TouchUpEvent : public Event
{
  static EventType GetType()
  {
    return EventType::TouchUp;
  }

  TouchUpEvent(float x, float y, int32 pointerID)
    : Event(EventType::TouchUp)
    , X(x)
    , Y(y)
    , PointerID(pointerID)
  {
  }

  float X;
  float Y;
  int32 PointerID;
};

struct TouchMoveEvent : public Event
{
  static EventType GetType()
  {
    return EventType::TouchMove;
  }

    TouchMoveEvent(float x, float y, int32 pointerID)
    : Event(EventType::TouchMove)
    , X(x)
    , Y(y)
    , PointerID(pointerID)
  {
  }

  float X;
  float Y;
  int32 PointerID;
};

typedef std::function<void(Event&)> EventCallback;

struct EventHandler
{
  EventCallback Callback;

  void CallEvent(Event& event)
  {
    if (Callback)
    {
      Callback(event);
    }
  }
};

struct EventSorter
{
  Event& e;

  EventSorter(Event& event)
    : e(event)
  {
  }

  template<typename T, typename Func>
  void SortEvent(const Func& func)
  {
    if (e.Type == T::GetType())
    {
      func(GetEvent<T>(e));
    }
  }
};

#define ZK_GET_EVENT_FUNCTION(name) [&](auto&&... args) { name(std::forward<decltype(args)>(args)...); }

ZK_NAMESPACE_END

#endif

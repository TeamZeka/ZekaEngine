#ifndef _H_EVENT
#define _H_EVENT

#include "Vector2.h"
#include "KeyCode.h"

#include <functional>
#include <utility>

ZK_NAMESPACE_BEGIN

enum class EventType : uint32
{
  WindowClose = 0,
  WindowSize,
  WindowMove,
  KeyDown,
  KeyUp,
  MouseButtonDown,
  MouseButtonUp,
  MouseMove,
  MouseWheel,
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

struct WindowMoveEvent : public Event
{
  static EventType GetType()
  {
    return EventType::WindowMove;
  }

  WindowMoveEvent(int x, int y)
    : Event(EventType::WindowMove)
    , X(x)
    , Y(y)
  {
  }

  int X;
  int Y;
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

struct MouseMoveEvent : public Event
{
  static EventType GetType()
  {
    return EventType::MouseMove;
  }

  MouseMoveEvent(const Vector2& pos)
    : Event(EventType::MouseMove)
    , Position(pos)
  {
  }

  Vector2 Position;
};

struct MouseWheelEvent : public Event
{
  static EventType GetType()
  {
    return EventType::MouseWheel;
  }

  MouseWheelEvent(const Vector2& axis)
    : Event(EventType::MouseWheel)
    , Axis(axis)
  {
  }

  Vector2 Axis;
};

struct TouchDownEvent : public Event
{
  static EventType GetType()
  {
    return EventType::TouchDown;
  }

  TouchDownEvent(const Vector2& pos, int32 pointerID)
    : Event(EventType::TouchDown)
    , Position(pos)
    , PointerID(pointerID)
  {
  }

  Vector2 Position;
  int32 PointerID;
};

struct TouchUpEvent : public Event
{
  static EventType GetType()
  {
    return EventType::TouchUp;
  }

  TouchUpEvent(const Vector2& pos, int32 pointerID)
    : Event(EventType::TouchUp)
    , Position(pos)
    , PointerID(pointerID)
  {
  }

  Vector2 Position;
  int32 PointerID;
};

struct TouchMoveEvent : public Event
{
  static EventType GetType()
  {
    return EventType::TouchMove;
  }

  TouchMoveEvent(const Vector2& pos, int32 pointerID)
    : Event(EventType::TouchMove)
    , Position(pos)
    , PointerID(pointerID)
  {
  }

  Vector2 Position;
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

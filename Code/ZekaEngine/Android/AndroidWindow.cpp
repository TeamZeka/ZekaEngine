#include "AndroidWindow.h"
#include "AndroidEngine.h"

#include "ZekaEngine/Platform.h"

ZK_NAMESPACE_BEGIN

struct AndroidKeyMap
{
  uint32 AndroidKeyCode;
  KeyCode EngineKeyCode;
};

AndroidKeyMap s_AndroidKeyMap[] =
{
  { AKEYCODE_HOME, KeyCode::Home },
  { AKEYCODE_BACK, KeyCode::Unknown },
  { AKEYCODE_0, KeyCode::Alpha0 },
  { AKEYCODE_1, KeyCode::Alpha1 },
  { AKEYCODE_2, KeyCode::Alpha2 },
  { AKEYCODE_3, KeyCode::Alpha3 },
  { AKEYCODE_4, KeyCode::Alpha4 },
  { AKEYCODE_5, KeyCode::Alpha5 },
  { AKEYCODE_6, KeyCode::Alpha6 },
  { AKEYCODE_7, KeyCode::Alpha7 },
  { AKEYCODE_8, KeyCode::Alpha8 },
  { AKEYCODE_9, KeyCode::Alpha9 },
  { AKEYCODE_STAR, KeyCode::NumpadMultiply },
  { AKEYCODE_VOLUME_UP, KeyCode::VolumeUp },
  { AKEYCODE_VOLUME_DOWN, KeyCode::VolumeDown },
  { AKEYCODE_CLEAR, KeyCode::Clear },
  { AKEYCODE_A, KeyCode::A },
  { AKEYCODE_B, KeyCode::B },
  { AKEYCODE_C, KeyCode::C },
  { AKEYCODE_D, KeyCode::D },
  { AKEYCODE_E, KeyCode::E },
  { AKEYCODE_F, KeyCode::F },
  { AKEYCODE_G, KeyCode::G },
  { AKEYCODE_H, KeyCode::H },
  { AKEYCODE_I, KeyCode::I },
  { AKEYCODE_J, KeyCode::J },
  { AKEYCODE_K, KeyCode::K },
  { AKEYCODE_L, KeyCode::L },
  { AKEYCODE_M, KeyCode::M },
  { AKEYCODE_N, KeyCode::N },
  { AKEYCODE_O, KeyCode::O },
  { AKEYCODE_P, KeyCode::P },
  { AKEYCODE_Q, KeyCode::Q },
  { AKEYCODE_R, KeyCode::R },
  { AKEYCODE_S, KeyCode::S },
  { AKEYCODE_T, KeyCode::T },
  { AKEYCODE_U, KeyCode::U },
  { AKEYCODE_V, KeyCode::V },
  { AKEYCODE_W, KeyCode::W },
  { AKEYCODE_Y, KeyCode::Y },
  { AKEYCODE_Z, KeyCode::Z },
  { AKEYCODE_COMMA, KeyCode::Comma },
  { AKEYCODE_PERIOD, KeyCode::Period },
  { AKEYCODE_ALT_LEFT, KeyCode::Alt },
  { AKEYCODE_ALT_RIGHT, KeyCode::Alt },
  { AKEYCODE_SHIFT_LEFT, KeyCode::Shift },
  { AKEYCODE_SHIFT_RIGHT, KeyCode::Shift },
  { AKEYCODE_TAB, KeyCode::Tab },
  { AKEYCODE_SPACE, KeyCode::Spacebar },
  { AKEYCODE_ENTER, KeyCode::Return },
  { AKEYCODE_DEL, KeyCode::Delete },
  { AKEYCODE_GRAVE, KeyCode::BackQuote },
  { AKEYCODE_MINUS, KeyCode::Minus },
  { AKEYCODE_PLUS, KeyCode::Plus },
  { AKEYCODE_LEFT_BRACKET, KeyCode::LeftBracket },
  { AKEYCODE_RIGHT_BRACKET, KeyCode::RightBracket },
  { AKEYCODE_BACKSLASH, KeyCode::Backslash },
  { AKEYCODE_SEMICOLON, KeyCode::Colon },
  { AKEYCODE_SLASH, KeyCode::Slash },
  { AKEYCODE_NUM, KeyCode::Numlock },
  { AKEYCODE_MENU, KeyCode::LeftMenu },
  { AKEYCODE_MEDIA_PLAY_PAUSE, KeyCode::MediaPlayPause },
  { AKEYCODE_MEDIA_STOP, KeyCode::MediaStop },
  { AKEYCODE_MEDIA_NEXT, KeyCode::MediaNextTrack },
  { AKEYCODE_MEDIA_PREVIOUS, KeyCode::MediaPrevTrack },
  { AKEYCODE_MUTE, KeyCode::VolumeMute },
  { AKEYCODE_PAGE_UP, KeyCode::PageUp },
  { AKEYCODE_PAGE_DOWN, KeyCode::PageDown },
  { AKEYCODE_ESCAPE, KeyCode::Escape },
  { AKEYCODE_CTRL_LEFT, KeyCode::Control },
  { AKEYCODE_CTRL_RIGHT, KeyCode::Control },
  { AKEYCODE_SCROLL_LOCK, KeyCode::Scroll },
  { AKEYCODE_BREAK, KeyCode::Pause },
  { AKEYCODE_MOVE_HOME, KeyCode::Home },
  { AKEYCODE_MOVE_END, KeyCode::End },
  { AKEYCODE_INSERT, KeyCode::Insert },
  { AKEYCODE_MEDIA_EJECT, KeyCode::LaunchMediaSelect },
  { AKEYCODE_F1, KeyCode::F1 },
  { AKEYCODE_F2, KeyCode::F2 },
  { AKEYCODE_F3, KeyCode::F3 },
  { AKEYCODE_F4, KeyCode::F4 },
  { AKEYCODE_F5, KeyCode::F5 },
  { AKEYCODE_F6, KeyCode::F6 },
  { AKEYCODE_F7, KeyCode::F7 },
  { AKEYCODE_F8, KeyCode::F8 },
  { AKEYCODE_F9, KeyCode::F9 },
  { AKEYCODE_F10, KeyCode::F10 },
  { AKEYCODE_F11, KeyCode::F11 },
  { AKEYCODE_F12, KeyCode::F12 },
  { AKEYCODE_NUM_LOCK, KeyCode::Numlock },
  { AKEYCODE_NUMPAD_0, KeyCode::Numpad0 },
  { AKEYCODE_NUMPAD_1, KeyCode::Numpad1 },
  { AKEYCODE_NUMPAD_2, KeyCode::Numpad2 },
  { AKEYCODE_NUMPAD_3, KeyCode::Numpad3 },
  { AKEYCODE_NUMPAD_4, KeyCode::Numpad4 },
  { AKEYCODE_NUMPAD_5, KeyCode::Numpad5 },
  { AKEYCODE_NUMPAD_6, KeyCode::Numpad6 },
  { AKEYCODE_NUMPAD_7, KeyCode::Numpad7 },
  { AKEYCODE_NUMPAD_8, KeyCode::Numpad8 },
  { AKEYCODE_NUMPAD_9, KeyCode::Numpad9 },
  { AKEYCODE_NUMPAD_DIVIDE, KeyCode::NumpadDivide },
  { AKEYCODE_NUMPAD_MULTIPLY, KeyCode::NumpadMultiply },
  { AKEYCODE_NUMPAD_SUBTRACT, KeyCode::NumpadSubtract },
  { AKEYCODE_NUMPAD_ADD, KeyCode::NumpadAdd },
  { AKEYCODE_NUMPAD_DOT, KeyCode::NumpadSeparator },
  { AKEYCODE_NUMPAD_COMMA, KeyCode::NumpadDecimal },
  { AKEYCODE_NUMPAD_ENTER, KeyCode::Return },
  { AKEYCODE_VOLUME_MUTE, KeyCode::VolumeMute },
  { AKEYCODE_HELP, KeyCode::Help },
  { AKEYCODE_KANA, KeyCode::Kana },
};

AndroidWindow::AndroidWindow(const char* name, EventHandler& handler)
  : Window(name, 0, 0, handler)
{
  m_pApp = static_cast<AndroidEngine*>(Engine::Get())->GetNativeApplication();
}

AndroidWindow::~AndroidWindow()
{
}

void AndroidWindow::HandleCmd(int32_t cmd)
{
  switch (cmd)
  {
  case APP_CMD_INIT_WINDOW:
  {
    ANativeWindow_acquire(m_pApp->window);

    m_Width = ANativeWindow_getWidth(m_pApp->window);
    m_Height = ANativeWindow_getHeight(m_pApp->window);

    Engine::Get()->GetWindow()->InitializeGraphics();
  } break;
  case APP_CMD_WINDOW_RESIZED:
  {
    const int width = ANativeWindow_getWidth(m_pApp->window);
    const int height = ANativeWindow_getHeight(m_pApp->window);

    OnWindowResized(width, height);

    m_Width = width;
    m_Height = height;
  } break;
  case APP_CMD_TERM_WINDOW:
  {
    Engine::Get()->GetWindow()->ShutdownGraphics();
    ANativeWindow_release(m_pApp->window);
  } break;
  }
}

int32_t AndroidWindow::HandleInput(AInputEvent* inputEvent)
{
  switch (AInputEvent_getType(inputEvent))
  {
  case AINPUT_EVENT_TYPE_MOTION:
  {
    const int32_t action = AMotionEvent_getAction(inputEvent);
    switch (action & AMOTION_EVENT_ACTION_MASK)
    {
    case AMOTION_EVENT_ACTION_DOWN:
    {
      const int32 pointerCount = (int32)AMotionEvent_getPointerCount(inputEvent);
      for (int32 i = 0; i < pointerCount; i++)
      {
        const int32 pointerId = AMotionEvent_getPointerId(inputEvent, i);
        const float x = AMotionEvent_getX(inputEvent, i);
        const float y = AMotionEvent_getY(inputEvent, i);
        OnTouchDown(x, y, pointerId);
      }
    } break;
    case AMOTION_EVENT_ACTION_UP:
    {
      const int32 pointerCount = (int32)AMotionEvent_getPointerCount(inputEvent);
      for (int32 i = 0; i < pointerCount; i++)
      {
        const int32 pointerId = AMotionEvent_getPointerId(inputEvent, i);
        const float x = AMotionEvent_getX(inputEvent, i);
        const float y = AMotionEvent_getY(inputEvent, i);
        OnTouchUp(x, y, pointerId);
      }
    } break;
    case AMOTION_EVENT_ACTION_MOVE:
    {
      const int32 pointerCount = (int32)AMotionEvent_getPointerCount(inputEvent);
      for (int32 i = 0; i < pointerCount; i++)
      {
        const int32 pointerId = AMotionEvent_getPointerId(inputEvent, i);
        const float x = AMotionEvent_getX(inputEvent, i);
        const float y = AMotionEvent_getY(inputEvent, i);
        OnTouchMove(x, y, pointerId);
      }
    } break;
    case AMOTION_EVENT_ACTION_POINTER_DOWN:
    {
      const int32 pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
      const int32 pointerId = AMotionEvent_getPointerId(inputEvent, pointerIndex);
      const float x = AMotionEvent_getX(inputEvent, pointerIndex);
      const float y = AMotionEvent_getY(inputEvent, pointerIndex);
      OnTouchDown(x, y, pointerId);
    } break;
    case AMOTION_EVENT_ACTION_POINTER_UP:
    {
      const int32 pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
      const int32 pointerId = AMotionEvent_getPointerId(inputEvent, pointerIndex);
      const float x = AMotionEvent_getX(inputEvent, pointerIndex);
      const float y = AMotionEvent_getY(inputEvent, pointerIndex);
      OnTouchUp(x, y, pointerId);
    } break;
    }
  } break;
  case AINPUT_EVENT_TYPE_KEY:
  {
    const int32 keyCode = AKeyEvent_getKeyCode(inputEvent);
    for (int32 i = 0; i < sizeof(s_AndroidKeyMap) / sizeof(s_AndroidKeyMap[0]); i++)
    {
      auto& eventType = s_AndroidKeyMap[i];
      if (eventType.AndroidKeyCode == keyCode) {
        bool isDown;
        const int32_t action = AKeyEvent_getAction(inputEvent);
        switch (action)
        {
        case AKEY_EVENT_ACTION_DOWN:
          isDown = true;
          break;
        case AKEY_EVENT_ACTION_MULTIPLE:
          isDown = (AKeyEvent_getRepeatCount(inputEvent) % 2) == 0;
          break;
        case AKEY_EVENT_ACTION_UP:
        default:
          isDown = false;
          break;
        }

        if (eventType.EngineKeyCode != KeyCode::Unknown)
        {
          if (isDown)
            OnKeyDown(eventType.EngineKeyCode);
          else
            OnKeyUp(eventType.EngineKeyCode);
        }

        return 1;
      }
    } break;
  }
  }

  return 0;
}

void AndroidWindow::PollEvents()
{
  android_poll_source* pSource;
  int events;
  if (ALooper_pollAll(0, nullptr, &events, (void**)&pSource) >= 0)
  {
    if (pSource)
    {
      pSource->process(m_pApp, pSource);
    }
  }
}

void* AndroidWindow::GetHandle() const
{
  return (void*)m_pApp->window;
}

bool AndroidWindow::DestroyRequested() const
{
  return m_pApp->destroyRequested;
}

Window* NewWindow(const char* name, int width, int height, EventHandler& handler)
{
  return new AndroidWindow(name, handler);
}

ZK_NAMESPACE_END

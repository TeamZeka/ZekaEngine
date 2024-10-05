#ifndef _H_KEY_CODE
#define _H_KEY_CODE

#include "HelperDefines.h"

ZK_NAMESPACE_BEGIN

enum class KeyCode : uint32
{
  Unknown = 0,

  Backspace = 0x08,
  Tab = 0x09,
  Clear = 0x0C,
  Return = 0x0D,
  Shift = 0x10,
  Control = 0x11,
  Alt = 0x12,
  Pause = 0x13,
  Capital = 0x14,
  Kana = 0x15,
  Hangul = 0x15,
  Junja = 0x17,
  Final = 0x18,
  Hanja = 0x19,
  Kanji = 0x19,
  Escape = 0x1B,
  Convert = 0x1C,
  Nonconvert = 0x1D,
  Accept = 0x1E,
  Modechange = 0x1F,
  Spacebar = 0x20,
  PageUp = 0x21,
  PageDown = 0x22,
  End = 0x23,
  Home = 0x24,
  ArrowLeft = 0x25,
  ArrowUp = 0x26,
  ArrowRight = 0x27,
  ArrowDown = 0x28,
  Select = 0x29,
  Print = 0x2A,
  Execute = 0x2B,
  PrintScreen = 0x2C,
  Insert = 0x2D,
  Delete = 0x2E,
  Help = 0x2F,
  Alpha0 = 0x30,
  Alpha1 = 0x31,
  Alpha2 = 0x32,
  Alpha3 = 0x33,

  /// <summary>
  /// The '4' key on the top of the alphanumeric keyboard.
  /// </summary>
  Alpha4 = 0x34,

  /// <summary>
  /// The '5' key on the top of the alphanumeric keyboard.
  /// </summary>
  Alpha5 = 0x35,

  /// <summary>
  /// The '6' key on the top of the alphanumeric keyboard.
  /// </summary>
  Alpha6 = 0x36,

  /// <summary>
  /// The '7' key on the top of the alphanumeric keyboard.
  /// </summary>
  Alpha7 = 0x37,

  /// <summary>
  /// The '8' key on the top of the alphanumeric keyboard.
  /// </summary>
  Alpha8 = 0x38,

  /// <summary>
  /// The '9' key on the top of the alphanumeric keyboard.
  /// </summary>
  Alpha9 = 0x39,

  /// <summary>
  /// A key
  /// </summary>
  A = 0x41,

  /// <summary>
  /// B key
  /// </summary>
  B = 0x42,

  /// <summary>
  /// C key
  /// </summary>
  C = 0x43,

  /// <summary>
  /// D key
  /// </summary>
  D = 0x44,

  /// <summary>
  /// E key
  /// </summary>
  E = 0x45,

  /// <summary>
  /// F key
  /// </summary>
  F = 0x46,

  /// <summary>
  /// G key
  /// </summary>
  G = 0x47,

  /// <summary>
  /// H key
  /// </summary>
  H = 0x48,

  /// <summary>
  /// I key
  /// </summary>
  I = 0x49,

  /// <summary>
  /// J key
  /// </summary>
  J = 0x4A,

  /// <summary>
  /// K key
  /// </summary>
  K = 0x4B,

  /// <summary>
  /// L key
  /// </summary>
  L = 0x4C,

  /// <summary>
  /// M key
  /// </summary>
  M = 0x4D,

  /// <summary>
  /// N key
  /// </summary>
  N = 0x4E,

  /// <summary>
  /// O key
  /// </summary>
  O = 0x4F,

  /// <summary>
  /// P key
  /// </summary>
  P = 0x50,

  /// <summary>
  /// Q key
  /// </summary>
  Q = 0x51,

  /// <summary>
  /// R key
  /// </summary>
  R = 0x52,

  /// <summary>
  /// S key
  /// </summary>
  S = 0x53,

  /// <summary>
  /// T key
  /// </summary>
  T = 0x54,

  /// <summary>
  /// U key
  /// </summary>
  U = 0x55,

  /// <summary>
  /// V key
  /// </summary>
  V = 0x56,

  /// <summary>
  /// W key
  /// </summary>
  W = 0x57,

  /// <summary>
  /// X key
  /// </summary>
  X = 0x58,

  /// <summary>
  /// Y key
  /// </summary>
  Y = 0x59,

  /// <summary>
  /// Z key
  /// </summary>
  Z = 0x5A,

  /// <summary>
  /// Left Windows key (Natural keyboard)
  /// </summary>
  LeftWindows = 0x5B,

  /// <summary>
  /// Right Windows key (Natural keyboard)
  /// </summary>
  RightWindows = 0x5C,

  /// <summary>
  /// Applications key (Natural keyboard)
  /// </summary>
  Applications = 0x5D,

  /// <summary>
  /// Computer Sleep key
  /// </summary>
  Sleep = 0x5F,

  /// <summary>
  /// Numeric keypad 0 key
  /// </summary>
  Numpad0 = 0x60,

  /// <summary>
  /// Numeric keypad 1 key
  /// </summary>
  Numpad1 = 0x61,

  /// <summary>
  /// Numeric keypad 2 key
  /// </summary>
  Numpad2 = 0x62,

  /// <summary>
  /// Numeric keypad 3 key
  /// </summary>
  Numpad3 = 0x63,

  /// <summary>
  /// Numeric keypad 4 key
  /// </summary>
  Numpad4 = 0x64,

  /// <summary>
  /// Numeric keypad 5 key
  /// </summary>
  Numpad5 = 0x65,

  /// <summary>
  /// Numeric keypad 6 key
  /// </summary>
  Numpad6 = 0x66,

  /// <summary>
  /// Numeric keypad 7 key
  /// </summary>
  Numpad7 = 0x67,

  /// <summary>
  /// Numeric keypad 8 key
  /// </summary>
  Numpad8 = 0x68,

  /// <summary>
  /// Numeric keypad 9 key
  /// </summary>
  Numpad9 = 0x69,

  /// <summary>
  /// Numeric keypad Multiply key '*'
  /// </summary>
  NumpadMultiply = 0x6A,

  /// <summary>
  /// Numeric keypad Add key '+'
  /// </summary>
  NumpadAdd = 0x6B,

  /// <summary>
  /// Numeric Separator key
  /// </summary>
  NumpadSeparator = 0x6C,

  /// <summary>
  /// Numeric keypad Subtract key '-'
  /// </summary>
  NumpadSubtract = 0x6D,

  /// <summary>
  /// Numeric keypad Decimal key ','
  /// </summary>
  NumpadDecimal = 0x6E,

  /// <summary>
  /// Numeric keypad Divide key '/'
  /// </summary>
  NumpadDivide = 0x6F,

  /// <summary>
  /// F1 function key
  /// </summary>
  F1 = 0x70,

  /// <summary>
  /// F2 function key
  /// </summary>
  F2 = 0x71,

  /// <summary>
  /// F3 function key
  /// </summary>
  F3 = 0x72,

  /// <summary>
  /// F4 function key
  /// </summary>
  F4 = 0x73,

  /// <summary>
  /// F5 function key
  /// </summary>
  F5 = 0x74,

  /// <summary>
  /// F6 function key
  /// </summary>
  F6 = 0x75,

  /// <summary>
  /// F7 function key
  /// </summary>
  F7 = 0x76,

  /// <summary>
  /// F8 function key
  /// </summary>
  F8 = 0x77,

  /// <summary>
  /// F9 function key
  /// </summary>
  F9 = 0x78,

  /// <summary>
  /// F10 function key
  /// </summary>
  F10 = 0x79,

  /// <summary>
  /// F11 function key
  /// </summary>
  F11 = 0x7A,

  /// <summary>
  /// F12 function key
  /// </summary>
  F12 = 0x7B,

  /// <summary>
  /// F13 function key
  /// </summary>
  F13 = 0x7C,

  /// <summary>
  /// F14 function key
  /// </summary>
  F14 = 0x7D,

  /// <summary>
  /// F15 function key
  /// </summary>
  F15 = 0x7E,

  /// <summary>
  /// F16 function key
  /// </summary>
  F16 = 0x7F,

  /// <summary>
  /// F17 function key
  /// </summary>
  F17 = 0x80,

  /// <summary>
  /// F18 function key
  /// </summary>
  F18 = 0x81,

  /// <summary>
  /// F19 function key
  /// </summary>
  F19 = 0x82,

  /// <summary>
  /// F20 function key
  /// </summary>
  F20 = 0x83,

  /// <summary>
  /// F21 function key
  /// </summary>
  F21 = 0x84,

  /// <summary>
  /// F22 function key
  /// </summary>
  F22 = 0x85,

  /// <summary>
  /// F23 function key
  /// </summary>
  F23 = 0x86,

  /// <summary>
  /// F24 function key
  /// </summary>
  F24 = 0x87,

  /// <summary>
  /// Numeric keypad NUM LOCK key
  /// </summary>
  Numlock = 0x90,

  /// <summary>
  /// SCROLL LOCK key
  /// </summary>
  Scroll = 0x91,

  /// <summary>
  /// Left MENU key
  /// </summary>
  LeftMenu = 0xA4,

  /// <summary>
  /// Right MENU key
  /// </summary>
  RightMenu = 0xA5,

  /// <summary>
  /// Browser Back key
  /// </summary>
  BrowserBack = 0xA6,

  /// <summary>
  /// Browser Forward key
  /// </summary>
  BrowserForward = 0xA7,

  /// <summary>
  /// Browser Refresh key
  /// </summary>
  BrowserRefresh = 0xA8,

  /// <summary>
  /// Browser Stop key
  /// </summary>
  BrowserStop = 0xA9,

  /// <summary>
  /// Browser Search key
  /// </summary>
  BrowserSearch = 0xAA,

  /// <summary>
  /// Browser Favorites key
  /// </summary>
  BrowserFavorites = 0xAB,

  /// <summary>
  /// Browser Start and Home key
  /// </summary>
  BrowserHome = 0xAC,

  /// <summary>
  /// Volume Mute key
  /// </summary>
  VolumeMute = 0xAD,

  /// <summary>
  /// Volume Down key
  /// </summary>
  VolumeDown = 0xAE,

  /// <summary>
  /// Volume Up key
  /// </summary>
  VolumeUp = 0xAF,

  /// <summary>
  /// Next Track key
  /// </summary>
  MediaNextTrack = 0xB0,

  /// <summary>
  /// Previous Track key
  /// </summary>
  MediaPrevTrack = 0xB1,

  /// <summary>
  /// Stop Media key
  /// </summary>
  MediaStop = 0xB2,

  /// <summary>
  /// Play/Pause Media key
  /// </summary>
  MediaPlayPause = 0xB3,

  /// <summary>
  /// Start Mail key
  /// </summary>
  LaunchMail = 0xB4,

  /// <summary>
  /// Select Media key
  /// </summary>
  LaunchMediaSelect = 0xB5,

  /// <summary>
  /// Start Application 1 key
  /// </summary>
  LaunchApp1 = 0xB6,

  /// <summary>
  /// Start Application 2 key
  /// </summary>
  LaunchApp2 = 0xB7,

  /// <summary>
  /// Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard the ';:' key
  /// </summary>
  Colon = 0xBA,

  /// <summary>
  /// For any country/region the '+' key
  /// </summary>
  Plus = 0xBB,
  Comma = 0xBC,
  Minus = 0xBD,
  Period = 0xBE,
  Slash = 0xBF,
  BackQuote = 0xC0,
  LeftBracket = 0xDB,
  Backslash = 0xDC,
  RightBracket = 0xDD,
  Quote = 0xDE,
  Oem8 = 0xDF,
  Oem102 = 0xE2,
  Processkey = 0xE5,
  Packet = 0xE7,
  Attn = 0xF6,
  Crsel = 0xF7,
  Exsel = 0xF8,
  Ereof = 0xF9,
  Play = 0xFA,
  Zoom = 0xFB,
  Pa1 = 0xFD,
  OemClear = 0xFE,

  MAX
};

enum class MouseButton : uint32
{
  Unknown = 0,

  Left,
  Middle,
  Right,
  XButton1,
  XButton2,

  MAX
};

#define ZK_MAX_KEY_CODE_NUMBER (uint32_t)KeyCode::MAX
#define ZK_MAX_MOUSE_BUTTON_NUMBER (uint32_t)MouseButton::MAX

ZK_NAMESPACE_END

#endif

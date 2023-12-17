#pragma once

namespace jupiter {

enum class EventType {
    UNKNOWN = 0,

    /* Keyboard events */
    KEYBOARD_PRESS = 768,
    KEYBOARD_RELEASE = 769,

    /* Mouse events */
    MOUSE_MOTION = 1024,
    MOUSE_PRESS = 1025,
    MOUSE_RELEASE = 1026,
    MOUSE_WHEEL_MOTION = 1027,

    /* Window events */
    WINDOW_CLOSE = 1800,
    WINDOW_RESIZE = 1801
};

namespace Keyboard {
enum Key {
    KEY_UNKNOWN = 0,

    KEY_SPACE = 32,
    KEY_APOSTROPHE = 39,
    KEY_COMMA = 44,
    KEY_MINUS = 45,
    KEY_PERIOD = 46,
    KEY_SLASH = 47,

    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,

    KEY_COLON = 58,
    KEY_SEMICOLON = 59,
    KEY_EQUAL = 61,

    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,

    KEY_ESCAPE = 256,
    KEY_ENTER = 257,
    KEY_TAB = 258,
    KEY_BACKSPACE = 259,
    KEY_INSERT = 260,
    KEY_DELETE = 261,
    KEY_RIGHT = 262,
    KEY_LEFT = 263,
    KEY_UP = 264,
    KEY_DOWN = 265,
    KEY_PAGEUP = 266,
    KEY_PAGEDOWN = 267,
    KEY_HOME = 268,
    KEY_END = 269,
    KEY_CAPSLOCK = 280,
    KEY_SCROLLLOCK = 281,
    KEY_NUMLOCK = 282,
    KEY_PRINTSCREEN = 283,
    KEY_PAUSE = 284,

    KEY_F1 = 290,
    KEY_F2 = 291,
    KEY_F3 = 292,
    KEY_F4 = 293,
    KEY_F5 = 294,
    KEY_F6 = 295,
    KEY_F7 = 296,
    KEY_F8 = 297,
    KEY_F9 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,

    KEY_NUMPAD_0 = 320,
    KEY_NUMPAD_1 = 321,
    KEY_NUMPAD_2 = 322,
    KEY_NUMPAD_3 = 323,
    KEY_NUMPAD_4 = 324,
    KEY_NUMPAD_5 = 325,
    KEY_NUMPAD_6 = 326,
    KEY_NUMPAD_7 = 327,
    KEY_NUMPAD_8 = 328,
    KEY_NUMPAD_9 = 329,
    KEY_NUMPAD_PERIOD = 330,
    KEY_NUMPAD_DIVIDE = 331,
    KEY_NUMPAD_MULTIPLY = 332,
    KEY_NUMPAD_SUBCTRACT = 333,
    KEY_NUMPAD_ADD = 334,
    KEY_NUMPAD_ENTER = 335,
    KEY_NUMPAD_EQUAL = 336,

    KEY_LEFT_SHIFT = 340,
    KEY_LEFT_CTRL = 341,
    KEY_LEFT_ALT = 342,
    KEY_LEFT_SUPER = 343,
    KEY_RIGHT_SHIFT = 344,
    KEY_RIGHT_CTRL = 345,
    KEY_RIGHT_ALT = 346,
    KEY_RIGHT_SUPER = 347,

    KEY_MENU = 348
};
}  // namespace Keyboard

namespace Mouse {
enum MouseKey { LEFT_BUTTON = 0, RIGHT_BUTTON = 1, MIDDLE_BUTTON = 2 };
}  // namespace Mouse

}  // namespace jupiter

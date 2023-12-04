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

    KEY_BACKSPACE = 8,
    KEY_ENTER = 13,
    KEY_ESCAPE = 27,
    KEY_SPACE = 32,
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
    KEY_LEFT_BRACKET = 91,
    KEY_RIGHT_BRACKET = 93,
    KEY_TILDA = 96,

    KEY_A = 'a',
    KEY_B = 'b',
    KEY_C = 'c',
    KEY_D = 'd',
    KEY_E = 'e',
    KEY_F = 'f',
    KEY_G = 'g',
    KEY_H = 'h',
    KEY_I = 'i',
    KEY_J = 'j',
    KEY_K = 'k',
    KEY_L = 'l',
    KEY_M = 'm',
    KEY_N = 'n',
    KEY_O = 'o',
    KEY_P = 'p',
    KEY_Q = 'q',
    KEY_R = 'r',
    KEY_S = 's',
    KEY_T = 't',
    KEY_U = 'u',
    KEY_V = 'v',
    KEY_W = 'w',
    KEY_X = 'x',
    KEY_Y = 'y',
    KEY_Z = 'z',

    KEY_DELETE = 127,

    KEY_F1 = 1073741882,
    KEY_F2 = 1073741883,
    KEY_F3 = 1073741884,
    KEY_F4 = 1073741885,
    KEY_F5 = 1073741886,
    KEY_F6 = 1073741887,
    KEY_F7 = 1073741888,
    KEY_F8 = 1073741889,
    KEY_F9 = 1073741890,
    KEY_F10 = 1073741891,
    KEY_F11 = 1073741892,
    KEY_F12 = 1073741893,
    KEY_PRINTSCREEN = 1073741894,
    KEY_SCROLLLOCK = 1073741895,
    KEY_PAUSE = 1073741896,
    KEY_INSERT = 1073741897,
    KEY_HOME = 1073741898,
    KEY_PAGEUP = 1073741899,
    KEY_END = 1073741901,
    KEY_PAGEDOWN = 1073741902,
    KEY_RIGHT = 1073741903,
    KEY_LEFT = 1073741904,
    KEY_DOWN = 1073741905,
    KEY_UP = 1073741906,
    KEY_NUMPAD_NUMLCOK = 1073741907,
    KEY_NUMPAD_DIVIDE = 1073741908,
    KEY_NUMPAD_MULTIPLY = 1073741909,
    KEY_NUMPAD_MINUS = 1073741910,
    KEY_NUMPAD_PLUS = 1073741911,
    KEY_NUMPAD_ENTER = 1073741912,
    KEY_NUMPAD_1 = 1073741913,
    KEY_NUMPAD_2 = 1073741914,
    KEY_NUMPAD_3 = 1073741915,
    KEY_NUMPAD_4 = 1073741916,
    KEY_NUMPAD_5 = 1073741917,
    KEY_NUMPAD_6 = 1073741918,
    KEY_NUMPAD_7 = 1073741919,
    KEY_NUMPAD_8 = 1073741920,
    KEY_NUMPAD_9 = 1073741921,
    KEY_NUMPAD_0 = 1073741922,
    KEY_NUMPAD_PERIOD = 1073741923,

    KEY_LEFT_CTRL = 1073742048
};
}  // namespace Keyboard

namespace Mouse {
enum MouseKey { UNKNOWN = 0, LEFT_BUTTON = 1, MIDDLE_BUTTON = 2, RIGHT_BUTTON = 3 };
}  // namespace Mouse

}  // namespace jupiter

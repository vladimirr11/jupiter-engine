#pragma once

// Own includes
#include "Event.h"

namespace jupiter {

class KeyEvent : public Event {
public:
    using KeyCode = Keyboard::Key;

    KeyCode getKeyCode() const { return key; }

protected:
    KeyEvent(const KeyCode key_) : key(key_) {}

protected:
    KeyCode key = KeyCode::KEY_UNKNOWN;  ///< Store pressed/released key
};

class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(const KeyCode keyCode, bool repeated_ = false)
        : KeyEvent(keyCode), repeated(repeated_) {}

    EVENT_TYPE(EventType::KEYBOARD_PRESS);

    bool isRepeated() const { return repeated; }

    std::string toString() const override { return fmt::format("Key {} pressed", (int32)key); }

private:
    bool repeated;  ///< Is the pressed key held
};

class KeyReleaseEvent : public KeyEvent {
public:
    KeyReleaseEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

    EVENT_TYPE(EventType::KEYBOARD_RELEASE);

    std::string toString() const override { return fmt::format("Key {} released", (int32)key); }
};

}  // namespace jupiter

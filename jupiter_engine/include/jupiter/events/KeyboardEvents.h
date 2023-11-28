#pragma once

// Own includes
#include "Event.h"

// Third-party includes
#include <fmt/format.h>

namespace jupiter {

class KeyEvent : public Event {
public:
    using KeyCode = Keyboard::Key;

    KeyCode getKeyCode() const { return key; }

protected:
    KeyEvent(const KeyCode key_) : key(key_) {}

protected:
    KeyCode key;  ///< Store pressed key
};

class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(const KeyCode keyCode, bool repeated_ = false)
        : KeyEvent(keyCode), repeated(repeated_) {}

    bool isRepeated() const { return repeated; }

    EventType getType() const override { return getStaticType(); }

    std::string toString() const override { return fmt::format("Key {} pressed\n", (int32_t)key); }

    static EventType getStaticType() { return eventType; }

private:
    bool repeated;  ///< Is the pressed key held
    constexpr static EventType eventType = EventType::KEYBOARD_PRESS;
};

class KeyReleaseEvent : public KeyEvent {
public:
    KeyReleaseEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

    EventType getType() const override { return getStaticType(); }

    std::string toString() const override { return fmt::format("Key {} released\n", (int32_t)key); }

    static EventType getStaticType() { return eventType; }

private:
    constexpr static EventType eventType = EventType::KEYBOARD_RELEASE;
};

}  // namespace jupiter
#pragma once

// Own includes
#include "Event.h"

namespace jupiter {

class MouseMotionEvent : public Event {
public:
    MouseMotionEvent(const float32 x, const float32 y) : mouseX(x), mouseY(y) {}

    EVENT_TYPE(EventType::MOUSE_MOTION);

    float32 getMouseX() const { return mouseX; }
    float32 getMouseY() const { return mouseY; }

    std::string toString() const override {
        return fmt::format("MouseX[{}], MouseY[{}]", getMouseX(), getMouseY());
    }

private:
    float32 mouseX{};
    float32 mouseY{};
};

class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(const float32 x, const float32 y) : xOffset(x), yOffset(y) {}

    EVENT_TYPE(EventType::MOUSE_WHEEL_MOTION);

    float32 getXOffset() const { return xOffset; }
    float32 getYOffset() const { return yOffset; }

    std::string toString() const override {
        return fmt::format("Mouse xOffset[{}], yOffset[{}]", getXOffset(), getYOffset());
    }

private:
    float32 xOffset{};
    float32 yOffset{};
};

class MouseButtonPressEvent : public Event {
    using MouseKeyCode = Mouse::MouseKey;

public:
    MouseButtonPressEvent(const MouseKeyCode button) : mouseButton(button) {}

    EVENT_TYPE(EventType::MOUSE_PRESS);

    std::string toString() const override {
        return fmt::format("Mouse {} button pressed", (int32)mouseButton);
    }

private:
    MouseKeyCode mouseButton;
};

class MouseButtonReleaseEvent : public Event {
    using MouseKeyCode = Mouse::MouseKey;

public:
    MouseButtonReleaseEvent(const MouseKeyCode button) : mouseButton(button) {}

    EVENT_TYPE(EventType::MOUSE_RELEASE);

    std::string toString() const override {
        return fmt::format("Mouse {} button released", (int32)mouseButton);
    }

private:
    MouseKeyCode mouseButton;
};

}  // namespace jupiter
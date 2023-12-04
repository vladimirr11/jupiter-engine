#pragma once

// Own includes
#include "Event.h"

namespace jupiter {

class MouseMotionEvent : public Event {
public:
    MouseMotionEvent(const float x, const float y) : mouseX(x), mouseY(y) {}

    EVENT_TYPE(EventType::MOUSE_MOTION);

    float getMouseX() const { return mouseX; }
    float getMouseY() const { return mouseY; }

    std::string toString() const override {
        return fmt::format("MouseX[{}], MouseY[{}]\n", getMouseX(), getMouseY());
    }

private:
    float mouseX{};
    float mouseY{};
};

class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(const float x, const float y) : xOffset(x), yOffset(y) {}

    EVENT_TYPE(EventType::MOUSE_WHEEL_MOTION);

    float getXOffset() const { return xOffset; }
    float getYOffset() const { return yOffset; }

    std::string toString() const override {
        return fmt::format("Mouse xOffset[{}], yOffset[{}]\n", getXOffset(), getYOffset());
    }

private:
    float xOffset{};
    float yOffset{};
};

class MouseButtonPressEvent : public Event {
    using MouseKeyCode = Mouse::MouseKey;

public:
    MouseButtonPressEvent(const MouseKeyCode button) : mouseButton(button) {}

    EVENT_TYPE(EventType::MOUSE_PRESS);

    std::string toString() const override {
        return fmt::format("Mouse {} button pressed\n", (int32_t)mouseButton);
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
        return fmt::format("Mouse {} button released\n", (int32_t)mouseButton);
    }

private:
    MouseKeyCode mouseButton;
};

}  // namespace jupiter
#pragma once

// Own includes
#include "Event.h"

namespace jupiter {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(const uint32_t width, const uint32_t height)
        : newWidth(width), newHeight(height) {}

    EVENT_TYPE(EventType::WINDOW_RESIZE);

    uint32_t getWidth() const { return newWidth; }
    uint32_t getHeight() const { return newHeight; }

    std::string toString() const override {
        return fmt::format("Window resized to [{}, {}]\n", newWidth, newHeight);
    }

private:
    uint32_t newWidth{};
    uint32_t newHeight{};
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_TYPE(EventType::WINDOW_CLOSE);
};

}  // namespace jupiter

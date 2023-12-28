#pragma once

// Own includes
#include "events/Event.h"

namespace jupiter {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(const uint32 width, const uint32 height)
        : newWidth(width), newHeight(height) {}

    EVENT_TYPE(EventType::WINDOW_RESIZE);

    uint32 getWidth() const { return newWidth; }
    uint32 getHeight() const { return newHeight; }

    std::string toString() const override {
        return fmt::format("Window resized to [{}, {}]", newWidth, newHeight);
    }

private:
    uint32 newWidth{};
    uint32 newHeight{};
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() = default;

    EVENT_TYPE(EventType::WINDOW_CLOSE);

    std::string toString() const override { return fmt::format("Window closed"); }
};

}  // namespace jupiter

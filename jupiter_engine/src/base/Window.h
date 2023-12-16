#pragma once

// C++ system includes
#include <string>

// Own includes
#include "events/Event.h"

namespace jupiter {

struct WindowConfig {
    std::string title;
    uint32 width, height;

    WindowConfig(const std::string& title_ = "Jupiter Engine", const uint32 width_ = 900,
                 const uint32 height_ = 700)
        : title(title_), width(width_), height(height_) {}
};

class Window {
public:
    virtual ~Window() = default;

    virtual void update() = 0;

    virtual uint32 getWidth() const = 0;
    virtual uint32 getHeight() const = 0;
    
    virtual void* getNativeWindow() const = 0;

    static UniquePtr<Window> create(const WindowConfig& config = WindowConfig());
};

}  // namespace jupiter

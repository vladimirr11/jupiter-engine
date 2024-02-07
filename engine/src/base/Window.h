#pragma once

// C++ system includes
#include <string>

// Own includes
#include "events/Event.h"
#include "renderer/GraphicsContext.h"

struct GLFWwindow;

namespace jupiter {

class GraphicsContext;

struct WindowConfig {
    std::string title;
    uint32 width, height;

    WindowConfig(const std::string& title_ = "Jupiter Engine", const uint32 width_ = 1200,
                 const uint32 height_ = 800)
        : title(title_), width(width_), height(height_) {}
};

class Window {
public:
    Window(const WindowConfig& config);
    virtual ~Window();

    virtual void update();

    virtual uint32 getWidth() const { return windowData.width; }
    virtual uint32 getHeight() const { return windowData.height; }

    virtual void* getNativeWindow() const { return window; }
    virtual GraphicsContext* getGraphicsContext() const { return context.get(); }
    virtual std::string getTitle() const { return windowData.title; }

    static UniquePtr<Window> create(const WindowConfig& config = WindowConfig());

private:
    struct WindowData {
        std::string title;
        uint32 width = 0u, height = 0u;
    };

    void init(const WindowConfig& config);
    void shutDown();

private:
    WindowData windowData;
    GLFWwindow* window = nullptr;
    UniquePtr<GraphicsContext> context = nullptr;
};

}  // namespace jupiter

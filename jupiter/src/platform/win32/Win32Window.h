#pragma once

// Own includes
#include "base/Window.h"
#include "renderer/opengl/GLContext.h"

struct GLFWwindow;

namespace jupiter {

class Win32Window : public Window {
public:
    Win32Window(const WindowConfig& config);

    ~Win32Window();

    void update() override;

    uint32 getWidth() const override { return windowData.width; }
    uint32 getHeight() const override { return windowData.height; }

    void* getNativeWindow() const override { return window; }
    GraphicsContext* getGraphicsContext() const override { return context.get(); }
    std::string getTitle() const { return windowData.title; }

private:
    struct Win32WindowData {
        std::string title;
        uint32 width, height;
    };

    void init(const WindowConfig& config);
    void shutDown();

private:
    Win32WindowData windowData;
    GLFWwindow* window = nullptr;
    UniquePtr<GraphicsContext> context = nullptr;
};

}  // namespace jupiter

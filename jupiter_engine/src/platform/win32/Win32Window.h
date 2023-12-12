#pragma once

// Own includes
#include "base/Window.h"

struct GLFWwindow;

namespace jupiter {

class Win32Window : public Window {
public:
    Win32Window(const WindowConfig& config);

    ~Win32Window();

    void onUpdate() override;

    inline uint32 getWidth() const override { return windowData.width; }
    inline uint32 getHeight() const override { return windowData.width; }

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
};

}  // namespace jupiter
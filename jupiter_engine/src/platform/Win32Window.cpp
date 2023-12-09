// Jpch
#include "Jpch.h"

// Own includes
#include "Win32Window.h"
#include "base/Assert.h"

// Trird-party inludes
#include <GLFW/glfw3.h>

namespace jupiter {

static bool glfwInitialized = false;

UniquePtr<Window> Window::create(const WindowConfig& config) {
    return createUniquePtr<Win32Window>(config);
}

Win32Window::Win32Window(const WindowConfig& config) { init(config); }

Win32Window::~Win32Window() { shutDown(); }

void Win32Window::onUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Win32Window::init(const WindowConfig& config) {
    windowData.title = config.title;
    windowData.width = config.width;
    windowData.height = config.height;

    // Initialize glfw
    if (!glfwInitialized) {
        jAssertFunc(glfwInit());
        JLOG_INFO("GLFW library initialized");
        glfwInitialized = true;
    }

    // Creat a window and context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    window = glfwCreateWindow((int32)config.width, (int32)config.height, config.title.c_str(),
                              nullptr, nullptr);
    jAssertPtr(window);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &windowData);

    // Enable vsync
    glfwSwapInterval(GLFW_TRUE);
}

void Win32Window::shutDown() { glfwDestroyWindow(window); }

}  // namespace jupiter
// Jpch
#include "Jpch.h"

// Own includes
#include "Win32Window.h"
#include "base/Assert.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"

// Trird-party includes
#include <GLFW/glfw3.h>

namespace jupiter {

static bool glfwInitialized = false;

UniquePtr<Window> Window::create(const WindowConfig& config) {
    return newUniquePtr<Win32Window>(config);
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

    // Creat window and context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    window = glfwCreateWindow((int32)config.width, (int32)config.height, config.title.c_str(),
                              nullptr, nullptr);
    jAssertPtr(window);
    JLOG_INFO("Window {} created", config.title);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &windowData);

    // Enable vsync
    glfwSwapInterval(GLFW_TRUE);

    // Set glfw event callbacks
    glfwSetWindowCloseCallback(
        window, [](GLFWwindow* glfwWindow) { triggerEvent(*newEvent<WindowCloseEvent>()); });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* glfwWindow, int32 width, int32 height) {
        Win32WindowData& data = *(Win32WindowData*)glfwGetWindowUserPointer(glfwWindow);
        data.width = width;
        data.height = height;
        triggerEvent(*newEvent<WindowResizeEvent>(width, height));
    });

    glfwSetKeyCallback(
        window, [](GLFWwindow* glfwWindow, int32 key, int32 scanCode, int32 action, int32 mods) {
            bool repeated = false;
            switch (action) {
            case GLFW_PRESS:
                triggerEvent(*newEvent<KeyPressEvent>((Keyboard::Key)key, repeated));
                break;
            case GLFW_REPEAT:
                repeated = true;
                triggerEvent(*newEvent<KeyPressEvent>((Keyboard::Key)key, repeated));
                break;
            case GLFW_RELEASE:
                triggerEvent(*newEvent<KeyReleaseEvent>((Keyboard::Key)key));
                break;
            default:
                JLOG_ERROR("Unsupported action provided in glfwSetKeyCallback function");
                jAssertExpr(false);
                break;
            }
        });
}

void Win32Window::shutDown() { glfwDestroyWindow(window); }

}  // namespace jupiter

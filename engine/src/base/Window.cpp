// Jpch
#include "Jpch.h"

// Own includes
#include "base/Window.h"
#include "base/Assert.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "renderer/opengl/GLContext.h"

// Third-party includes
#include <GLFW/glfw3.h>

namespace jupiter {

static bool glfwInitialized = false;

UniquePtr<Window> Window::create(const WindowConfig& config) {
    return newUniquePtr<Window>(config);
}

Window::Window(const WindowConfig& config) { init(config); }
Window::~Window() { shutDown(); }

void Window::update() {
    context->swapBuffers();
    glfwPollEvents();
}

void Window::init(const WindowConfig& config) {
    windowData.title = config.title;
    windowData.width = config.width;
    windowData.height = config.height;

    // Initialize GLFW
    if (!glfwInitialized) {
        jAssertFunc(glfwInit());
        JLOG_INFO("GLFW library initialized");
        glfwInitialized = true;
    }

    // Create window and context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow((int32)config.width, (int32)config.height, config.title.c_str(),
                              nullptr, nullptr);
    jAssertPtr(window);
    JLOG_INFO("Window {} created", config.title);

    // Create graphics context
    context = newUniquePtr<GLContext>(window);
    jAssertPtr(context);
    context->init();

    // Associate _windowData_ to the window in order to be retrieved latter with
    // glfwGetWindowUserPointer
    glfwSetWindowUserPointer(window, &windowData);

    // Enable GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Enable vSync
    glfwSwapInterval(GLFW_TRUE);

    // Set GLFW event callbacks
    // Register function to be called on window close event
    glfwSetWindowCloseCallback(window, [](GLFWwindow* glfwWindow) {
        // triggerEvent(WindowCloseEvent());
        queueEvent(newEvent<WindowCloseEvent>());
    });

    // Register function to be called on window resize event
    glfwSetWindowSizeCallback(window, [](GLFWwindow* glfwWindow, int32 width, int32 height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(glfwWindow);
        data.width = width;
        data.height = height;
        // triggerEvent(WindowResizeEvent(width, height));
        queueEvent(newEvent<WindowResizeEvent>(width, height));
    });

    // Register function to be called on keyboard event
    glfwSetKeyCallback(
        window, [](GLFWwindow* glfwWindow, int32 key, int32 scanCode, int32 action, int32 mods) {
            bool repeated = false;
            switch (action) {
            case GLFW_PRESS:
                // triggerEvent(KeyPressEvent((Keyboard::Key)key, repeated));
                queueEvent(newEvent<KeyPressEvent>((Keyboard::Key)key, repeated));
                break;
            case GLFW_REPEAT:
                repeated = true;
                // triggerEvent(KeyPressEvent((Keyboard::Key)key, repeated));
                queueEvent(newEvent<KeyPressEvent>((Keyboard::Key)key, repeated));
                break;
            case GLFW_RELEASE:
                // triggerEvent(KeyReleaseEvent((Keyboard::Key)key));
                queueEvent(newEvent<KeyReleaseEvent>((Keyboard::Key)key));
                break;
            default:
                JLOG_ERROR("Unsupported action provided in glfwSetKeyCallback function");
                jAssertExpr(false);
            }
        });

    // Register function to be called on mouse button pressed or released event
    glfwSetMouseButtonCallback(
        window, [](GLFWwindow* glfwWindow, int32 mouseButton, int32 action, int32 mods) {
            switch (action) {
            case GLFW_PRESS: {
                // triggerEvent(MouseButtonPressEvent((Mouse::MouseKey)mouseButton));
                queueEvent(newEvent<MouseButtonPressEvent>((Mouse::MouseKey)mouseButton));
                break;
            }
            case GLFW_RELEASE:
                // triggerEvent(MouseButtonReleaseEvent((Mouse::MouseKey)mouseButton));
                queueEvent(newEvent<MouseButtonReleaseEvent>((Mouse::MouseKey)mouseButton));
                break;
            default:
                JLOG_ERROR("Unsupported action provided in glfwSetMouseButtonCallback function");
                jAssertExpr(false);
            }
        });

    // Register function to be called on mouse move event
    glfwSetCursorPosCallback(window, [](GLFWwindow* glfwWindow, float64 xPos, float64 yPos) {
        // triggerEvent(MouseMotionEvent((float32)xPos, (float32)yPos));
        queueEvent(newEvent<MouseMotionEvent>((float32)xPos, (float32)yPos));
    });

    // Register function to be called on mouse scroll event
    glfwSetScrollCallback(window, [](GLFWwindow* glfwWindow, float64 xOffset, float64 yOffset) {
        // triggerEvent(MouseScrollEvent((float32)xOffset, (float32)yOffset));
        queueEvent(newEvent<MouseScrollEvent>((float32)xOffset, (float32)yOffset));
    });
}

void Window::shutDown() { glfwDestroyWindow(window); }

}  // namespace jupiter

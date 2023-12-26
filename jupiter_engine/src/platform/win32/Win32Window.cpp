// Jpch
#include "Jpch.h"

// Own includes
#include "platform/win32/Win32Window.h"
#include "base/Assert.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"

namespace jupiter {

static bool glfwInitialized = false;

UniquePtr<Window> Window::create(const WindowConfig& config) {
    return newUniquePtr<Win32Window>(config);
}

Win32Window::Win32Window(const WindowConfig& config) { init(config); }

Win32Window::~Win32Window() { shutDown(); }

void Win32Window::update() {
    context->swapBuffers();
    glfwPollEvents();
    int32 windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
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

    glfwSetWindowUserPointer(window, &windowData);

    // Enable vsync
    glfwSwapInterval(GLFW_TRUE);

    // Set glfw event callbacks
    // Window callbacks
    glfwSetWindowCloseCallback(
        window, [](GLFWwindow* glfwWindow) { queueEvent(newEvent<WindowCloseEvent>()); });

    glfwSetWindowSizeCallback(window, [](GLFWwindow* glfwWindow, int32 width, int32 height) {
        Win32WindowData& data = *(Win32WindowData*)glfwGetWindowUserPointer(glfwWindow);
        data.width = width;
        data.height = height;
        queueEvent(newEvent<WindowResizeEvent>(width, height));
    });

    // Keyborad callbacks
    glfwSetKeyCallback(
        window, [](GLFWwindow* glfwWindow, int32 key, int32 scanCode, int32 action, int32 mods) {
            bool repeated = false;
            switch (action) {
            case GLFW_PRESS:
                queueEvent(newEvent<KeyPressEvent>((Keyboard::Key)key, repeated));
                break;
            case GLFW_REPEAT:
                repeated = true;
                queueEvent(newEvent<KeyPressEvent>((Keyboard::Key)key, repeated));
                break;
            case GLFW_RELEASE:
                queueEvent(newEvent<KeyReleaseEvent>((Keyboard::Key)key));
                break;
            default:
                JLOG_ERROR("Unsupported action provided in glfwSetKeyCallback function");
                jAssertExpr(false);
            }
        });

    // Mouse callbacks
    glfwSetMouseButtonCallback(
        window, [](GLFWwindow* glfwWindow, int32 mouseButton, int32 action, int32 mods) {
            switch (action) {
            case GLFW_PRESS:
                queueEvent(newEvent<MouseButtonPressEvent>((Mouse::MouseKey)mouseButton));
                break;
            case GLFW_RELEASE:
                queueEvent(newEvent<MouseButtonReleaseEvent>((Mouse::MouseKey)mouseButton));
                break;
            default:
                JLOG_ERROR("Unsupported action provided in glfwSetMouseButtonCallback function");
                jAssertExpr(false);
            }
        });

    glfwSetCursorPosCallback(window, [](GLFWwindow* glfwWindow, float64 xPos, float64 yPos) {
        queueEvent(newEvent<MouseMotionEvent>((float32)xPos, (float32)yPos));
    });

    glfwSetScrollCallback(window, [](GLFWwindow* glfwWindow, float64 xOffset, float64 yOffset) {
        queueEvent(newEvent<MouseScrollEvent>((float32)xOffset, (float32)yOffset));
    });
}

void Win32Window::shutDown() { glfwDestroyWindow(window); }

}  // namespace jupiter

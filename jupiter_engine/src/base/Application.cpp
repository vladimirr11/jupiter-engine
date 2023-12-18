// Jpch
#include "Jpch.h"

// Own includes
#include "base/Application.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "ui/imgui/ImGuiUiLayer.h"
#include "Input.h"
#include "math/matrix/Transform.h"

namespace jupiter {

Application* Application::appInstance = nullptr;

Application::Application() {
    appInstance = this;

    // Initialize global linear allocator for input events
    gLinearAllocator = newUniquePtr<LinearAllocator>(1e6);
    jAssertPtr(gLinearAllocator);

    // Initialize global event manager
    gEventManager = newUniquePtr<EventManager>();
    jAssertPtr(gEventManager);

    // Create window
    window = Window::create();
    jAssertPtr(window);

    // Create UI layer
    uiLayer = newUniquePtr<ImGuiUILayer>();
    uiLayer->init(UILayerConfig(window.get()));
    jAssertPtr(uiLayer);

    // Window events handlers
    subscribe<WindowCloseEvent>([this](const WindowCloseEvent& event) { onWindowClose(event); });
    subscribe<WindowResizeEvent>([this](const WindowResizeEvent& event) { onEvent(event); });
    // Keyboard events handlers
    subscribe<KeyPressEvent>([this](const KeyPressEvent& event) { onEvent(event); });
    subscribe<KeyReleaseEvent>([this](const KeyReleaseEvent& event) { onEvent(event); });
    // Mouse events handlers
    subscribe<MouseButtonPressEvent>(
        [this](const MouseButtonPressEvent& event) { onEvent(event); });
    subscribe<MouseButtonReleaseEvent>(
        [this](const MouseButtonReleaseEvent& event) { onEvent(event); });
    subscribe<MouseMotionEvent>([this](const MouseMotionEvent& event) { onEvent(event); });
    subscribe<MouseScrollEvent>([this](const MouseScrollEvent& event) { onEvent(event); });
}

Application::~Application() {}

void Application::run() {
    jm::Vec4f vec4(1.145f, .34f, 7.45f, 2.12f);
    jm::Matrix4x4 mat4;
    mat4 = jm::rotate(mat4, 15.f, jm::Vec3f(1.0f, 1.0f, 1.0f));
    vec4 = mat4 * vec4;

    while (running) {
        window->update();
        uiLayer->update();

        // Dispatch event queue
        dispatchEvents();
    }
}

void Application::onWindowClose(const WindowCloseEvent& event) {
    running = false;
    JLOG_INFO(event.toString().c_str());
}

void Application::onEvent(const Event& event) { JLOG_INFO(event.toString().c_str()); }

}  // namespace jupiter

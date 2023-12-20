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

    // Attach UI layer
    uiLayer = newUniquePtr<ImGuiUILayer>();
    uiLayer->attach(UILayerConfig(window.get()));
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
    jm::Matrix4x4 view = jm::lookAt(jm::Vec3f(0.4f, 1.8f, 3.0f), jm::Vec3f(6.0f, 2.4f, 0.0f));
    JLOG_INFO(toString(view).c_str());

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

void Application::onEvent(const Event& event) {
    JLOG_INFO(event.toString().c_str());
    if (Input::isKeyPressed(Keyboard::KEY_ESCAPE)) {
        running = false;
    }
}

}  // namespace jupiter

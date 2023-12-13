// Jpch
#include "Jpch.h"

// Own includes
#include "base/Application.h"
#include "base/Assert.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "memory/LinearAllocator.h"

namespace jupiter {

Application::Application() {
    // Initialize global linear allocator for input events
    gLinearAllocator = newUniquePtr<LinearAllocator>(1e6);
    jAssertPtr(gLinearAllocator);

    // Initialize global event manager
    gEventManager = newUniquePtr<EventManager>();
    jAssertPtr(gEventManager);

    // Create window
    window = Window::create();

    // Window events
    subscribe<WindowCloseEvent>([this](const WindowCloseEvent& event) { onWindowClose(event); });
    subscribe<WindowResizeEvent>([this](const WindowResizeEvent& event) { onEvent(event); });
    // Keyboard events
    subscribe<KeyPressEvent>([this](const KeyPressEvent& event) { onEvent(event); });
    subscribe<KeyReleaseEvent>([this](const KeyReleaseEvent& event) { onEvent(event); });
    // Mouse events
    subscribe<MouseButtonPressEvent>(
        [this](const MouseButtonPressEvent& event) { onEvent(event); });
    subscribe<MouseButtonReleaseEvent>(
        [this](const MouseButtonReleaseEvent& event) { onEvent(event); });
    subscribe<MouseMotionEvent>([this](const MouseMotionEvent& event) { onEvent(event); });
    subscribe<MouseScrollEvent>([this](const MouseScrollEvent& event) { onEvent(event); });
}

Application::~Application() {}

void Application::run() {
    while (running) {
        window->update();

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

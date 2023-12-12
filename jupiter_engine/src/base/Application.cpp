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

    window = Window::create();

    subscribe<WindowCloseEvent>([this](const WindowCloseEvent& event) { onWindowClose(event); });
    subscribe<WindowResizeEvent>([this](const WindowResizeEvent& event) { onEvent(event); });
    subscribe<KeyPressEvent>([this](const KeyPressEvent& event) { onEvent(event); });
    subscribe<KeyReleaseEvent>([this](const KeyReleaseEvent& event) { onEvent(event); });
}

Application::~Application() {}

void Application::run() {
    while (running) {
        window->onUpdate();

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

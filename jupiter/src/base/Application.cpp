// Jpch
#include "Jpch.h"

// Own includes
#include "base/Application.h"
#include "base/Input.h"
#include "base/Timer.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "renderer/Renderer.h"
#include "ui/imgui/ImGuiUILayer.h"

namespace jupiter {

Application* Application::appInstance = nullptr;

Application::Application() {
    appInstance = this;

    // Initialize global memory arena for storing of all input events
    gMemoryArena = newUniquePtr<MemoryArena>(1e6);
    jAssertPtr(gMemoryArena);

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

    // Initialize renderer
    Renderer::init();

    // Window events handlers
    subscribe<WindowCloseEvent>([this](const WindowCloseEvent& event) { onWindowClose(event); });
    subscribe<WindowResizeEvent>([this](const WindowResizeEvent& event) { onWindowResize(event); });
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

Application::~Application() { Renderer::shutDown(); }

void Application::run() {
    DeltaTime::init();
    while (running) {
        // Dispatch event queue
        dispatchEvents();

        // Update render logic and camera movement wrt frame rate
        update(DeltaTime::getFrameRate<float32>());

        // Render UI layer
        uiLayer->update(std::bind(&Application::uiLayerUpdate, this));

        // Swap buffers and poll IO events
        window->update();
    }
}

void Application::onWindowClose(const WindowCloseEvent& event) {
    running = false;
    JLOG_INFO(event.toString().c_str());
}

void Application::onWindowResize(const WindowResizeEvent& event) {
    Renderer::Command::setViewport(event.getWidth(), event.getHeight());
}

void Application::onEvent(const Event& event) {
    JLOG_INFO(event.toString().c_str());
    if (Input::keyPressed(Keyboard::KEY_ESCAPE)) {
        running = false;
    }
}

}  // namespace jupiter

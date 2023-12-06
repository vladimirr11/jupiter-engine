// Jpch
#include "Jpch.h"

// Corresponding header
#include "base/Application.h"

// C++ system includes
#include <iostream>

// Own includes
#include "base/Assert.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "memory/LinearAllocator.h"

namespace jupiter {

Application::Application() {}

Application::~Application() {}

void Application::run() {
    gEventManager = new EventManager();

    LinearAllocator allocator(1024 * 1024);

    /// keyboard events
    auto pressCKey = allocator.create<KeyPressEvent>(Keyboard::KEY_C);
    auto pressZKey = allocator.create<KeyPressEvent>(Keyboard::KEY_Z);
    auto releaseZKey = allocator.create<KeyReleaseEvent>(Keyboard::KEY_Z);

    gEventManager->queueEvent(pressCKey);
    gEventManager->queueEvent(pressZKey);
    gEventManager->queueEvent(releaseZKey);

    auto onKeyPressFunc = [](const KeyPressEvent& event) { std::cout << event.toString(); };
    auto onKeyReleaseFunc = [](const KeyReleaseEvent& event) { std::cout << event.toString(); };

    auto eventHandlerKeyPressed = allocator.create<EventHandler<KeyPressEvent>>(onKeyPressFunc);
    auto eventHandlerKeyReleased =
        allocator.create<EventHandler<KeyReleaseEvent>>(onKeyReleaseFunc);

    gEventManager->subscribe(EventType::KEYBOARD_PRESS, eventHandlerKeyPressed);
    gEventManager->subscribe(EventType::KEYBOARD_RELEASE, eventHandlerKeyReleased);

    //// mouse events
    auto mouseMotionEvent = allocator.create<MouseMotionEvent>(0.34, 0.67);
    auto mouseScrollEvent = allocator.create<MouseScrollEvent>(4.35, 9.45);
    auto mousePress = allocator.create<MouseButtonPressEvent>(Mouse::LEFT_BUTTON);
    auto mouseRelease = allocator.create<MouseButtonReleaseEvent>(Mouse::LEFT_BUTTON);

    gEventManager->queueEvent(mouseMotionEvent);
    gEventManager->queueEvent(mouseScrollEvent);
    gEventManager->queueEvent(mousePress);
    gEventManager->queueEvent(mouseRelease);

    auto onMouseMotionFunc = [](const MouseMotionEvent& event) { std::cout << event.toString(); };
    auto onMouseScrollFunc = [](const MouseScrollEvent& event) { std::cout << event.toString(); };
    auto onMouseButtonPresFunc = [](const MouseButtonPressEvent& event) {
        std::cout << event.toString();
    };
    auto onMouseButtonReleaseFunc = [](const MouseButtonReleaseEvent& event) {
        std::cout << event.toString();
    };

    auto eventHandlerMouseMove =
        allocator.create<EventHandler<MouseMotionEvent>>(onMouseMotionFunc);
    auto eventHandlerMouseScroll =
        allocator.create<EventHandler<MouseScrollEvent>>(onMouseScrollFunc);
    auto eventHandlerMouseButtonPress =
        allocator.create<EventHandler<MouseButtonPressEvent>>(onMouseButtonPresFunc);
    auto eventHandlerMouseButtonRelease =
        allocator.create<EventHandler<MouseButtonReleaseEvent>>(onMouseButtonReleaseFunc);

    gEventManager->subscribe(EventType::MOUSE_MOTION, eventHandlerMouseMove);
    gEventManager->subscribe(EventType::MOUSE_WHEEL_MOTION, eventHandlerMouseScroll);
    gEventManager->subscribe(EventType::MOUSE_PRESS, eventHandlerMouseButtonPress);
    gEventManager->subscribe(EventType::MOUSE_RELEASE, eventHandlerMouseButtonRelease);

    // window events
    // 1. Create event
    auto windowResize = allocator.create<WindowResizeEvent>(400, 600);

    // 2. Queue event
    gEventManager->queueEvent(windowResize);

    // 3. Event callback
    auto onWindowResizeFunc = [](const WindowResizeEvent& event) { std::cout << event.toString(); };

    // 4. Attach callback to event handler
    auto eventHandlerWindowResize =
        allocator.create<EventHandler<WindowResizeEvent>>(onWindowResizeFunc);

    // 5. Subscribe event handler for event
    gEventManager->subscribe(EventType::WINDOW_RESIZE, eventHandlerWindowResize);

    // execute events
    // 6. Trigger event
    gEventManager->dispatchEvents();
    gEventManager->shutDown();

    // infinite loop
    for (;;)
        ;
}

}  // namespace jupiter

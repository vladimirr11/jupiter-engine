// Jpch
#include "jupiter/Jpch.h"

// Corresponding header
#include "jupiter/base/Application.h"

// Own includes
#include "jupiter/events/EventManager.h"
#include "jupiter/events/KeyboardEvents.h"
#include "jupiter/events/MouseEvents.h"
#include "jupiter/events/WindowEvents.h"
#include "jupiter/base/Assert.h"

namespace jupiter {

Application::Application() {}

Application::~Application() {}

void Application::run() {
    gEventManager = new EventManager();

    // keyboard events
    auto pressCKey = std::make_unique<KeyPressEvent>(Keyboard::KEY_C);
    auto pressZKey = std::make_unique<KeyPressEvent>(Keyboard::KEY_Z);
    auto releaseZKey = std::make_unique<KeyReleaseEvent>(Keyboard::KEY_Z);

    gEventManager->queueEvent(std::move(pressCKey));
    gEventManager->queueEvent(std::move(pressZKey));
    gEventManager->queueEvent(std::move(releaseZKey));

    auto onKeyPressFunc = [](const KeyPressEvent& event) { std::cout << event.toString(); };
    auto onKeyReleaseFunc = [](const KeyReleaseEvent& event) { std::cout << event.toString(); };

    auto eventHandlerKeyPressed = std::make_unique<EventHandler<KeyPressEvent>>(onKeyPressFunc);
    auto eventHandlerKeyReleased =
        std::make_unique<EventHandler<KeyReleaseEvent>>(onKeyReleaseFunc);

    gEventManager->subscribe(EventType::KEYBOARD_PRESS, std::move(eventHandlerKeyPressed));
    gEventManager->subscribe(EventType::KEYBOARD_RELEASE, std::move(eventHandlerKeyReleased));

    // mouse events
    auto mouseMotionEvent = std::make_unique<MouseMotionEvent>(0.34, 0.67);
    auto mouseScrollEvent = std::make_unique<MouseScrollEvent>(4.35, 9.45);
    auto mousePress = std::make_unique<MouseButtonPressEvent>(Mouse::LEFT_BUTTON);
    auto mouseRelease = std::make_unique<MouseButtonReleaseEvent>(Mouse::LEFT_BUTTON);

    gEventManager->queueEvent(std::move(mouseMotionEvent));
    gEventManager->queueEvent(std::move(mouseScrollEvent));
    gEventManager->queueEvent(std::move(mousePress));
    gEventManager->queueEvent(std::move(mouseRelease));

    auto onMouseMotionFunc = [](const MouseMotionEvent& event) { std::cout << event.toString(); };
    auto onMouseScrollFunc = [](const MouseScrollEvent& event) { std::cout << event.toString(); };
    auto onMouseButtonPresFunc = [](const MouseButtonPressEvent& event) {
        std::cout << event.toString();
    };
    auto onMouseButtonReleaseFunc = [](const MouseButtonReleaseEvent& event) {
        std::cout << event.toString();
    };

    auto eventHandlerMouseMove =
        std::make_unique<EventHandler<MouseMotionEvent>>(onMouseMotionFunc);
    auto eventHandlerMouseScroll =
        std::make_unique<EventHandler<MouseScrollEvent>>(onMouseScrollFunc);
    auto eventHandlerMouseButtonPress =
        std::make_unique<EventHandler<MouseButtonPressEvent>>(onMouseButtonPresFunc);
    auto eventHandlerMouseButtonRelease =
        std::make_unique<EventHandler<MouseButtonReleaseEvent>>(onMouseButtonReleaseFunc);

    gEventManager->subscribe(EventType::MOUSE_MOTION, std::move(eventHandlerMouseMove));
    gEventManager->subscribe(EventType::MOUSE_WHEEL_MOTION, std::move(eventHandlerMouseScroll));
    gEventManager->subscribe(EventType::MOUSE_PRESS, std::move(eventHandlerMouseButtonPress));
    gEventManager->subscribe(EventType::MOUSE_RELEASE, std::move(eventHandlerMouseButtonRelease));

    // window events
    // 1. Create event
    auto windowResize = std::make_unique<WindowResizeEvent>(400, 600);

    // 2. Queue event
    gEventManager->queueEvent(std::move(windowResize));

    // 3. Event callback
    auto onWindowResizeFunc = [](const WindowResizeEvent& event) { std::cout << event.toString(); };

    // 4. Attach callback to event handler
    auto eventHandlerWindowResize =
        std::make_unique<EventHandler<WindowResizeEvent>>(onWindowResizeFunc);

    // 5. Subscribe event handler for event
    gEventManager->subscribe(EventType::WINDOW_RESIZE, std::move(eventHandlerWindowResize));

    // execute events
    // 6. Trigger event
    gEventManager->dispatchEvents();
    gEventManager->shutDown();

    // infinite loop
    for (;;)
        ;
}

}  // namespace jupiter

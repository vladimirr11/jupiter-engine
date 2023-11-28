// Corresponding header
#include "jupiter/Application.h"

// Own includes
#include "jupiter/events/EventManager.h"
#include "jupiter/events/KeyboardEvents.h"

#include <iostream>

namespace jupiter {

Application::Application() {}

Application::~Application() {}

void Application::run() {
    gEventManager = new EventManager();

    auto pressCKey = std::make_unique<KeyPressEvent>(Keyboard::KEY_C);
    auto pressDKey = std::make_unique<KeyPressEvent>(Keyboard::KEY_D);
    auto pressZKey = std::make_unique<KeyPressEvent>(Keyboard::KEY_Z);

    gEventManager->queueEvent(std::move(pressCKey));
    gEventManager->queueEvent(std::move(pressZKey));
    gEventManager->queueEvent(std::move(pressDKey));

    auto onKeyPressFunc = [](const KeyPressEvent& event) { std::cout << event.toString(); };

    auto eventHandlerKeyPressed = std::make_unique<EventHandler<KeyPressEvent>>(onKeyPressFunc);

    gEventManager->subscribe(EventType::KEYBOARD_PRESS, std::move(eventHandlerKeyPressed));

    gEventManager->dispatchEvents();

    gEventManager->shutDown();

    for (;;)
        ;
}

}  // namespace jupiter

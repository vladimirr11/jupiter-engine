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

Application::Application() { window = Window::create(); }

Application::~Application() {}

void Application::run() {
    while (running) {
        window->onUpdate();
    }
}

}  // namespace jupiter

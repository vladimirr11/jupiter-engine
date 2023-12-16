#pragma once

// Own includes
#include "Window.h"

namespace jupiter {

class WindowCloseEvent;
class UILayer;
class Event;

class JUPITER_API Application {
public:
    Application();
    virtual ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void onWindowClose(const WindowCloseEvent& event);
    void onEvent(const Event& event);

private:
    UniquePtr<Window> window;
    UniquePtr<UILayer> uiLayer;
    bool running = true;
};

Application* createApplication();

}  // namespace jupiter

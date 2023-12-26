#pragma once

// Own includes
#include "base/Window.h"

namespace jupiter {

class WindowCloseEvent;
class UILayer;
class Event;

class Application {
public:
    Application();
    virtual ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    static Application& instance() { return *appInstance; }
    inline Window& getWindow() { return *window.get(); }

    void run();

private:
    void onWindowClose(const WindowCloseEvent& event);
    void onEvent(const Event& event);

private:
    UniquePtr<Window> window;
    UniquePtr<UILayer> uiLayer;
    bool running = true;
    static Application* appInstance;
};

Application* createApplication();

inline void* getAppNativeWindow() { 
    return Application::instance().getWindow().getNativeWindow(); 
}

}  // namespace jupiter

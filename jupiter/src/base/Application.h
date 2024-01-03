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
    virtual ~Application() = default;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    static Application& instance() { return *appInstance; }
    inline Window& getWindow() { return *window.get(); }

    void run();

protected:
    // Protected virtual methods to be overridden by the client app
    virtual void init() {}
    virtual void update(const float32 deltaTime) {}
    virtual void shutDown() {}

private:
    void onWindowClose(const WindowCloseEvent& event);
    void onEvent(const Event& event);

private:
    UniquePtr<Window> window;
    UniquePtr<UILayer> uiLayer;
    bool running = true;
    static Application* appInstance;
};

inline void* getAppNativeWindow() { return Application::instance().getWindow().getNativeWindow(); }

inline GraphicsContext* getAppGraphicsContext() {
    return Application::instance().getWindow().getGraphicsContext();
}

// Should be implemented by the Client
Application* createApplication();

}  // namespace jupiter

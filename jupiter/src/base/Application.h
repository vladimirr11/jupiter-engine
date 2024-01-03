#pragma once

// Own includes
#include "base/Window.h"

// Temp inludes
#include "cameras/OrthographicCamera.h"

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
    void update(const float32 deltaTime);

private:
    UniquePtr<Window> window;
    UniquePtr<UILayer> uiLayer;
    bool running = true;
    static Application* appInstance;
    
    // TODO: remove me ------
    SharedPtr<OrthographicCamera> camera = nullptr;
    jm::Vec3f cameraPos;
    float32 cameraMoveSpeed = 1.5f;
    // ----------------------
};

inline void* getAppNativeWindow() { 
    return Application::instance().getWindow().getNativeWindow(); 
}

inline GraphicsContext* getAppGraphicsContext() { 
    return Application::instance().getWindow().getGraphicsContext(); 
}

// Should be implemented by the Client
Application* createApplication();

}  // namespace jupiter

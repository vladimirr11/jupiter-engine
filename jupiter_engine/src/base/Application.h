#pragma once

// Own includes
#include "BaseDefines.h"
#include "Window.h"

namespace jupiter {

struct WindowCloseEvent;
struct Event;

class JUPITER_API Application {
public:
    Application();

    virtual ~Application();

    void run();

private:
    void onWindowClose(const WindowCloseEvent& event);
    void onEvent(const Event& event);

private:
    UniquePtr<Window> window;
    bool running = true;
};

Application* createApplication();

}  // namespace jupiter

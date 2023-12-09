#pragma once

// Own includes
#include "BaseDefines.h"
#include "Window.h"

namespace jupiter {

class JUPITER_API Application {
public:
    Application();

    virtual ~Application();

    void run();

private:
    UniquePtr<Window> window;
    bool running = true;
};

Application* createApplication();

}  // namespace jupiter

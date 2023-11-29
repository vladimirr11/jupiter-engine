#pragma once

// Own includes
#include "CommonDefines.h"

namespace jupiter {

class JUPITER_API Application {
public:
    Application();

    virtual ~Application();

    void run();
};

Application* createApplication();

}  // namespace jupiter

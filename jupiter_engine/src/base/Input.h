#pragma once

// Own includes
#include "base/Basedefines.h"

namespace jupiter {

class Input {
public:
    static bool isKeyPressed(const int32 key);
    static bool isMouseButtonPressed(const int32 mouseButton);
    static std::pair<float32, float32> getMousePosition();
};

}  // namespace jupiter
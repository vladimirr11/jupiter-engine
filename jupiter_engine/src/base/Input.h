#pragma once

// Own includes
#include "base/Basedefines.h"
#include "math/vector/Vector.h"

namespace jupiter {

class Input {
public:
    static bool isKeyPressed(const int32 key);
    static bool isMouseButtonPressed(const int32 mouseButton);
    static jm::Vec2f getMousePosition();
};

}  // namespace jupiter
#pragma once

// Own includes
#include "base/Defines.h"
#include "math/vector/Vector.h"

namespace jupiter {

class Input {
public:
    static bool keyPressed(const int32 key);
    static bool mouseButtonPressed(const int32 mouseButton);
    static jm::Vec2f getMousePosition();
};

}  // namespace jupiter

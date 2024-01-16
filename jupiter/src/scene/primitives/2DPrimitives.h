#pragma once

// C++ system includes
#include <vector>

// Own includes
#include "math/vector/Vector.h"

namespace jupiter {

struct Quad {
    jm::Vec3f position;
    jm::Vec3f size;
    jm::Vec4f color;
    // jm::Vec2f texCoords;
    // uint32 id;
};

}  // namespace jupiter

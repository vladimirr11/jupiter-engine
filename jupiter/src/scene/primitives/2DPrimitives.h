#pragma once

// Own includes
#include "math/vector/Vector.h"

namespace jupiter {

struct Quad {
    jm::Vec3f position;
    jm::Vec3f size;
    jm::Vec4f color;
    jm::Vec2f texCoords;
    uint32 texScaler = 1u;
};

}  // namespace jupiter

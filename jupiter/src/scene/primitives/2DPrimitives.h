#pragma once

// Own includes
#include "math/vector/Vector.h"

namespace jupiter {

struct QuadDescription {
    jm::Vec3f position;
    jm::Vec3f size;
    jm::Vec4f color = jm::Vec4f(1.f);
    bool useTexture = false;
    uint32 texScaler = 1u;
    float32 rotation = 0.f;
};

}  // namespace jupiter

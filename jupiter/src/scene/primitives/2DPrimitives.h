#pragma once

// Own includes
#include "math/vector/Vector.h"
#include "renderer/Texture.h"

namespace jupiter {

/// @brief Quad description data passed from client for drawing
struct QuadDescription {
    jm::Vec3f position;
    jm::Vec2f size;
    jm::Vec4f color = jm::Vec4f(1.f);
    SharedPtr<Texture2D> texture = nullptr;
    float32 texScaler = 1.f;
    float32 rotation = 0.f;
};

/// @brief Quad vertex data passed to vertex shader
struct QuadVertex {
    jm::Vec4f position;
    jm::Vec4f color;
    jm::Vec2f texCoords;
    float32 texScaler;
    float32 texSlot;
};

}  // namespace jupiter

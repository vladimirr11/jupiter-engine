#pragma once

// Own includes
#include "base/BaseDefines.h"

static constexpr float32 PI = 3.14159265358979323846f;
static constexpr float32 PIOver180 = PI / 180.f;

namespace jupiter {

inline constexpr float32 deg2Radians(const float32 degrees) { return degrees * PIOver180; }

}  // namespace jupiter

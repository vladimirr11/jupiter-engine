#pragma once

// Own includes
#include "base/BaseDefines.h"
#include <numeric>

static constexpr float32 PI = 3.14159265358979323846f;
static constexpr float32 PIOver180 = PI / 180.f;

namespace jm {

inline constexpr float32 deg2Radians(const float32 degrees) { return degrees * PIOver180; }

template <typename T>
inline T abs(T value) {
    return std::abs(value);
}

template <typename T>
using eps = std::numeric_limits<T>::epsilon();

}  // namespace jm

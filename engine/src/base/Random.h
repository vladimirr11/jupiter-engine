#pragma once

// C++ systme includes
#include <random>
#include <iostream>

// Own includes
#include "base/Defines.h"

namespace jupiter {

class Random {
public:
    static void init() { engine.seed(std::random_device()()); }

    static int32 getInt32(const int32 from = 0, const int32 to = 1) {
        static std::uniform_int_distribution<int32> uniformDist(from, to);
        return uniformDist(engine);
    }

    static float32 getFloat32(const float32 from = 0.f, const float32 to = 1.f) {
        static std::uniform_real_distribution<float32> realDist(from, to);
        return realDist(engine);
    }

private:
    inline static std::mt19937 engine;
};

}  // namespace jupiter

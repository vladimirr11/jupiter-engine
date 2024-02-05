#pragma once

// C++ system includes
#include <chrono>

// Own includes
#include "base/Defines.h"

namespace jupiter {

class Timer {
public:
    Timer() {}

    void start() { startPoint = clock::now(); }

    template <typename T>
    static T toSec(T nanosec) {
        return T(nanosec / 1e9);
    }

    template <typename T>
    static T toMilliSec(T nanosec) {
        return T(nanosec / 1e6);
    }

    template <typename T>
    static T toMicroSec(T nanosec) {
        return T(nanosec / 1e3);
    }

    int64 getElapsedNanoSec() const {
        const clock::time_point now = clock::now();
        return std::chrono::duration_cast<nanosec>(now - startPoint).count();
    }

private:
    using clock = std::chrono::steady_clock;
    using nanosec = std::chrono::nanoseconds;

    clock::time_point startPoint;  ///< Timer start point
};

class DeltaTime {
public:
    DeltaTime() = delete;

    static void init() { timer.start(); }

    template <typename T>
    static T getFrameRate() {
        T currFrameRate = Timer::toSec<T>((T)timer.getElapsedNanoSec());
        T deltaTime = currFrameRate - lastFrameRate<T>;
        lastFrameRate<T> = currFrameRate;
        return deltaTime;
    }

private:
    inline static Timer timer;  ///< Static timer
    ///< Variable template to keep the execution time of the previous frame
    template <typename T>
    inline static T lastFrameRate = 0.f;
};

}  // namespace jupiter
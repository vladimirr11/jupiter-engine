#pragma once

// C++ system includes
#include <cmath>
#include <sstream>

// Own includes
#include "base/Assert.h"

namespace jm {

template <typename T>
struct Vector2 {
    union {
        struct {
            T x, y;
        };
        T v2[2];
    };

    // Ctors
    Vector2() : x(0), y(0) {}

    Vector2(const T s) : x(s), y(s) {}

    Vector2(const T x_, const T y_) : x(x_), y(y_) {}

    // Element access
    T& operator[](const int32 i) {
        jAssertExpr(i >= 0 && i < 2);
        return v2[i];
    }

    const T& operator[](const int32 i) const {
        jAssertExpr(i >= 0 && i < 2);
        return v2[i];
    }

    // Arithmetic operations
    Vector2<T> operator+(const Vector2& vec2) const { return Vector2(x + vec2.x, y + vec2.y); }

    Vector2<T>& operator+=(const Vector2& vec2) {
        x += vec2.x;
        y += vec2.y;
        return *this;
    }

    Vector2<T> operator-(const Vector2& vec2) const { return Vector2(x - vec2.x, y - vec2.y); }

    Vector2<T>& operator-=(const Vector2& vec2) {
        x -= vec2.x;
        y -= vec2.y;
        return *this;
    }

    template <typename U>
    Vector2<T> operator*(const U s) const {
        return Vector2(x * s, y * s);
    }

    template <typename U>
    Vector2<T>& operator*=(const U s) {
        x *= s;
        y *= s;
        return *this;
    }

    template <typename U>
    Vector2<T> operator/(const U s) const {
        float32 inv = (float32)1 / s;
        return *this * inv;
    }

    template <typename U>
    Vector2<T>& operator/=(const U s) {
        float32 inv = (float32)1 / s;
        return *this *= inv;
    }

    // Comparison operators
    bool operator==(const Vector2& vec2) const { return x == vec2.x && y == vec2.y; }

    bool operator!=(const Vector2& vec2) const { return !(*this == vec2); }

    // Negation operator
    Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

    // Vector length
    float32 norm() const { return sqrtf(x * x + y * y); }
};

template <typename T>
inline Vector2<T> normalize2(const Vector2<T>& vec2) {
    jAssertExpr(vec2.norm() != 0);
    return vec2 / vec2.norm();
}

template <typename T>
inline T dot2(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline bool isZeroVector(const Vector2<T>& vec2) {
    const T zero = static_cast<T>(0);
    return vec2.y == zero && vec2.x == zero;
}

template <typename T>
inline std::string toString(const Vector2<T>& vec2) {
    std::stringstream stream;
    stream << "[" << vec2.x << ", " << vec2.y << "]";
    return stream.str();
}

}  // namespace jm

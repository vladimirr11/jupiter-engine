#pragma once

// Own includes
#include "Vector2.h"

namespace jm {

template <typename T>
struct Vector3 {
    union {
        struct {
            T x, y, z;
        };
        T v3[3];
    };

    // Ctors
    Vector3() : x(0), y(0), z(0) {}

    Vector3(const T s) : x(s), y(s), z(s) {}

    Vector3(const T x_, const T y_, const T z_) : x(x_), y(y_), z(z_) {}

    Vector3(const Vector2<T>& vec2, const T z_) : x(vec2.x), y(vec2.y), z(z_) {}

    // Element access
    T& operator[](const int32 i) {
        jAssertExpr(i >= 0 && i < 3);
        return v3[i];
    }

    const T& operator[](const int32 i) const {
        jAssertExpr(i >= 0 && i < 3);
        return v3[i];
    }

    // Arithmetic operations
    Vector3<T> operator+(const Vector3& vec3) const {
        return Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
    }

    Vector3<T>& operator+=(const Vector3& vec3) {
        x += vec3.x;
        y += vec3.y;
        z += vec3.z;
        return *this;
    }

    Vector3<T> operator-(const Vector3& vec3) const {
        return Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
    }

    Vector3<T>& operator-=(const Vector3& vec3) {
        x -= vec3.x;
        y -= vec3.y;
        z -= vec3.z;
        return *this;
    }

    template <typename U>
    Vector3<T> operator*(const U s) const {
        return Vector3(x * s, y * s, z * s);
    }

    template <typename U>
    Vector3<T>& operator*=(const U s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    template <typename U>
    Vector3<T> operator/(const U s) const {
        float32 inv = (float32)1 / s;
        return *this * inv;
    }

    template <typename U>
    Vector3<T>& operator/=(const U s) {
        float32 inv = (float32)1 / s;
        return *this *= inv;
    }

    // Comparison operators
    bool operator==(const Vector3& vec3) const { return x == vec3.x && y == vec3.y && z == vec3.z; }

    bool operator!=(const Vector3& vec3) const { return !(*this == vec3); }

    // Negation operator
    Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }

    // Vector length
    float32 norm() const { return sqrtf(x * x + y * y + z * z); }
};

template <typename T>
inline Vector3<T> normalize3(const Vector3<T>& vec3) {
    jAssertExpr(vec3.norm() != 0);
    return vec3 / vec3.norm();
}

template <typename T>
inline T dot3(const Vector3<T>& v1, const Vector3<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2) {
    return Vector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
                      v1.x * v2.y - v1.y * v2.x);
}

template <typename T>
inline std::string toString(const Vector3<T>& vec3) {
    std::stringstream stream;
    stream << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
    return stream.str();
}

}  // namespace jm

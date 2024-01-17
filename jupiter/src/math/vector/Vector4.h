#pragma once

// Own includes
#include "Vector3.h"

namespace jm {

template <typename T>
struct Vector4 {
    union {
        struct {
            T x, y, z, w;
        };
        T v4[4];
    };

    // Ctors
    Vector4() : x(0), y(0), z(0), w(0) {}

    Vector4(const T s) : x(s), y(s), z(s), w(s) {}

    Vector4(const T x_, const T y_, const T z_, const T w_) : x(x_), y(y_), z(z_), w(w_) {}

    Vector4(const Vector3<T>& vec3, const T w_) : x(vec3.x), y(vec3.y), z(vec3.z), w(w_) {}

    // Element access
    T& operator[](const int32 i) {
        jAssertExpr(i >= 0 && i < 4);
        return v4[i];
    }

    const T& operator[](const int32 i) const {
        jAssertExpr(i >= 0 && i < 4);
        return v4[i];
    }

    // Arithmetic operations
    Vector4<T> operator+(const Vector4& vec4) const {
        return Vector4(x + vec4.x, y + vec4.y, z + vec4.z, w + vec4.w);
    }

    Vector4<T>& operator+=(const Vector4& vec4) {
        x += vec4.x;
        y += vec4.y;
        z += vec4.z;
        w += vec4.w;
        return *this;
    }

    Vector4<T> operator-(const Vector4& vec4) const {
        return Vector4(x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w);
    }

    Vector4<T>& operator-=(const Vector4& vec4) {
        x -= vec4.x;
        y -= vec4.y;
        z -= vec4.z;
        w -= vec4.w;
        return *this;
    }

    template <typename U>
    Vector4<T> operator*(const U s) const {
        return Vector4(x * s, y * s, z * s, w * s);
    }

    template <typename U>
    Vector4<T>& operator*=(const U s) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }

    template <typename U>
    Vector4<T> operator/(const U s) const {
        float32 inv = (float32)1 / s;
        return *this * inv;
    }

    template <typename U>
    Vector4<T>& operator/=(const U s) {
        float32 inv = (float32)1 / s;
        return *this *= inv;
    }

    // Comparison operators
    bool operator==(const Vector4& vec4) const {
        return x == vec4.x && y == vec4.y && z == vec4.z && w == vec4.w;
    }

    bool operator!=(const Vector4& vec4) const { return !(*this == vec4); }

    // Negation operator
    Vector4<T> operator-() const { return Vector3<T>(-x, -y, -z, -w); }

    // Vector length
    float32 norm() const { return sqrtf(x * x + y * y + z * z + w * w); }
};

template <typename T>
inline Vector4<T> normalize4(const Vector4<T>& vec4) {
    jAssertExpr(vec4.norm() != 0);
    return vec4 / vec4.norm();
}

template <typename T>
inline T dot4(const Vector4<T>& v1, const Vector4<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template <typename T>
inline bool isZeroVector(const Vector4<T>& vec4) {
    const T zero = static_cast<T>(0);
    return vec4.w == zero && vec4.z == zero && vec4.y == zero && vec4.x == zero;
}

template <typename T>
inline std::string toString(const Vector4<T>& vec4) {
    std::stringstream stream;
    stream << "[" << vec4.x << ", " << vec4.y << ", " << vec4.z << ", " << vec4.w << "]";
    return stream.str();
}

}  // namespace jm

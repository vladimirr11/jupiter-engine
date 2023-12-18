#pragma once

// Own includes
#include "Matrix4x4.h"

namespace jm {

/// @brief Creates 4x4 scale matrix from a vector of 3 scalars
inline Matrix4x4 scale(const Matrix4x4& mat4, const Vec3f& vec3) {
    Matrix4x4 result;
    result.col[0] = mat4.col[0] * vec3[0];
    result.col[1] = mat4.col[1] * vec3[1];
    result.col[2] = mat4.col[2] * vec3[2];
    result.col[3] = mat4.col[3];
    return result;
}

/// @brief Creates 4x4 translation matrix from a vector of 3 components
inline Matrix4x4 translate(const Matrix4x4& mat4, const Vec3f& vec3) {
    Matrix4x4 result(mat4);
    result.col[3] =
        mat4.col[0] * vec3[0] + mat4.col[1] * vec3[1] + mat4.col[2] * vec3[2] + mat4.col[3];
    return result;
}

/// @brief Creates 4x4 rotation matrix from an axis vector and an angle
template <typename T>
inline Matrix4x4 rotate(const Matrix4x4& mat4, const T theta, const Vec3f& vec3) {
    const float32 cosTheta = cos(theta);
    const float32 sinTheta = sin(theta);
    const Vec3f axis = normalize3(vec3);

    Matrix4x4 result;
    result[0][0] = cosTheta + (1 - cosTheta) * axis[0] * axis[0];
    result[0][1] = (1 - cosTheta) * axis[0] * axis[1] + sinTheta * axis[2];
    result[0][2] = (1 - cosTheta) * axis[0] * axis[2] - sinTheta * axis[1];
    result[0][3] = 0.f;

    result[1][0] = (1 - cosTheta) * axis[1] * axis[0] - sinTheta * axis[2];
    result[1][1] = cosTheta + (1 - cosTheta) * axis[1] * axis[1];
    result[1][2] = (1 - cosTheta) * axis[1] * axis[2] + sinTheta * axis[0];
    result[1][3] = 0.f;

    result[2][0] = (1 - cosTheta) * axis[2] * axis[0] + sinTheta * axis[1];
    result[2][1] = (1 - cosTheta) * axis[2] * axis[1] - sinTheta * axis[0];
    result[2][2] = cosTheta + (1 - cosTheta) * axis[2] * axis[2];
    result[2][3] = 0.f;

    result[3] = Vec4f(0.f, 0.f, 0.f, 1.f);

    return mat4 * result;
}

}  // namespace jm

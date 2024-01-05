#pragma once

// Own includes
#include "math/matrix/Matrix4x4.h"

#define RIGHT_HANDED_COORD_SYSTEM

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

/// @brief Creates an orthographic projection matrix using right or left-handed coordinates.
/// Created clip volume is in the range -1 to +1 (OpenGL defalut clip volume)
template <typename T>
inline Matrix4x4 ortho(const T left, const T right, const T bottom, const T top,
                       const T near = 0.1f, const T far = 100.f) {
    Matrix4x4 result;
    result[0][0] = 2.f / (right - left);
    result[1][1] = 2.f / (top - bottom);
#ifdef RIGHT_HANDED_COORD_SYSTEM
    result[2][2] = -2.f / (far - near);
#else
    result[2][2] = 2.f / (far - near);
#endif  // RIGHT_HANDED_COORD_SYSTEM
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);
    return result;
}

/// @brief Creates a prespective projection matrix using right or left-handed coordinates.
/// Created clip volume is in the range -1 to +1 (OpenGL defalut clip volume)
template <typename T>
inline Matrix4x4 prespective(const T fov, const T aspect, const T near = 0.1f,
                             const T far = 100.f) {
    jAssertExpr(abs(aspect - std::numeric_limits<T>::epsilon()) > 0.f);
    const T tanFalfFov = tan(fov / 2.f);

    Matrix4x4 result(0.f);
    result[0][0] = 1.f / (aspect * tanFalfFov);
    result[1][1] = 1.f / tanFalfFov;
    result[2][2] = -(far + near) / (far - near);
#ifdef RIGHT_HANDED_COORD_SYSTEM
    result[2][3] = -1.f;
#else
    result[2][3] = 1.f;
#endif  // RIGHT_HANDED_COORD_SYSTEM
    result[3][2] = -(2.f * far * near) / (far - near);
    return result;
}

/// @brief Creates a look at view matrix using right or left-handed coordinates
inline Matrix4x4 lookAt(const Vec3f& pos, const Vec3f& target,
                        const Vec3f& up = Vec3f(0.f, 1.f, 0.f)) {
    const Vec3f zVec = normalize3(target - pos);
#ifdef RIGHT_HANDED_COORD_SYSTEM
    const Vec3f xVec = normalize3(cross(zVec, up));
    const Vec3f yVec = cross(xVec, zVec);
#else
    const Vec3f xVec = normalize3(cross3(up, zVec));
    const Vec3f yVec = cross3(zVec, xVec);
#endif  // RIGHT_HANDED_COORD_SYSTEM

    Matrix4x4 result;
    result[0][0] = xVec.x;
    result[1][0] = xVec.y;
    result[2][0] = xVec.z;
    result[0][1] = yVec.x;
    result[1][1] = yVec.y;
    result[2][1] = yVec.z;
#ifdef RIGHT_HANDED_COORD_SYSTEM
    result[0][2] = -zVec.x;
    result[1][2] = -zVec.y;
    result[2][2] = -zVec.z;
    result[3][0] = -dot3(xVec, pos);
    result[3][1] = -dot3(yVec, pos);
    result[3][2] = dot3(zVec, pos);
#else
    result[0][2] = zVec.x;
    result[1][2] = zVec.y;
    result[2][2] = zVec.z;
    result[3][0] = -dot3(xVec, pos);
    result[3][1] = -dot3(yVec, pos);
    result[3][2] = -dot3(zVec, pos);
#endif  // RIGHT_HANDED_COORD_SYSTEM

    return result;
}

}  // namespace jm

#pragma once

// Own includes
#include "math/vector/Vector.h"
#include "math/MathUtils.h"

namespace jm {

struct Matrix4x4 {
    // Ctor - Identity matrix
    Matrix4x4() { m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f; }

    Matrix4x4(const float32 mat[4][4]) { memcpy(m, mat, 16 * sizeof(float32)); }

    // Ctor that takes 4 column vectors
    Matrix4x4(const Vec4f& cv0, const Vec4f& cv1, const Vec4f& cv2, const Vec4f& cv3) {
        m[0][0] = cv0.x, m[0][1] = cv0.y, m[0][2] = cv0.z, m[0][3] = cv0.w;
        m[1][0] = cv1.x, m[1][1] = cv1.y, m[1][2] = cv1.z, m[1][3] = cv1.w;
        m[2][0] = cv2.x, m[2][1] = cv2.y, m[2][2] = cv2.z, m[2][3] = cv2.w;
        m[3][0] = cv3.x, m[3][1] = cv3.y, m[3][2] = cv3.z, m[3][3] = cv3.w;
    }

    // Vector access
    Vec4f& operator[](const int32 i) {
        jAssertExpr(i >= 0 && i < 4);
        return col[i];
    }

    const Vec4f& operator[](const int32 i) const {
        jAssertExpr(i >= 0 && i < 4);
        return col[i];
    }

    // Matrix4x4 friends
    friend Matrix4x4 transpose(const Matrix4x4& m);
    friend Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
    friend Vec4f operator*(const Matrix4x4& mat4, const Vec4f& vev4);

    // Matrix4x4 data
    union {
        float32 m[4][4]{};  ///< Zero initialized 4x4 column major matrix
        Vec4f col[4];       ///< Each row in the matrix represents a column vector
    };
};

Matrix4x4 transpose(const Matrix4x4& mat4) {
    return Matrix4x4(Vec4f(mat4.m[0][0], mat4.m[1][0], mat4.m[2][0], mat4.m[3][0]),
                     Vec4f(mat4.m[0][1], mat4.m[1][1], mat4.m[2][1], mat4.m[3][1]),
                     Vec4f(mat4.m[0][2], mat4.m[1][2], mat4.m[2][2], mat4.m[3][2]),
                     Vec4f(mat4.m[0][3], mat4.m[1][3], mat4.m[2][3], mat4.m[3][3]));
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;
    for (int32 i = 0; i < 4; ++i)
        for (int32 j = 0; j < 4; ++j)
            result.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] +
                             m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
    return result;
}

Vec4f operator*(const Matrix4x4& mat4, const Vec4f& vec4) {
    Vec4f result;
    result[0] =
        mat4[0][0] * vec4.x + mat4[1][0] * vec4.y + mat4[2][0] * vec4.z + mat4[3][0] * vec4.w;
    result[1] =
        mat4[0][1] * vec4.x + mat4[1][1] * vec4.y + mat4[2][1] * vec4.z + mat4[3][1] * vec4.w;
    result[2] =
        mat4[0][2] * vec4.x + mat4[1][2] * vec4.y + mat4[2][2] * vec4.z + mat4[3][2] * vec4.w;
    result[3] =
        mat4[0][3] * vec4.x + mat4[1][3] * vec4.y + mat4[2][3] * vec4.z + mat4[3][3] * vec4.w;
    return result;
}

}  // namespace jm

#pragma once

// Own includes
#include "math/vector/Vector.h"
#include "math/MathUtils.h"

namespace jm {

struct Matrix4x4 {
    // Ctor - Identity matrix
    Matrix4x4() { m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f; }

    // Ctor - Main diagonal
    Matrix4x4(const float32 diag) { m[0][0] = m[1][1] = m[2][2] = diag; }

    // Ctor - row array
    Matrix4x4(const float32 mat[4][4]) { memcpy(m, mat, 16 * sizeof(float32)); }

    // Copy ctor
    Matrix4x4(const Matrix4x4& other) { memcpy(m, other.m, 16 * sizeof(float32)); }

    // Copy assignment
    Matrix4x4 operator=(const Matrix4x4& rhs) {
        if (this != &rhs) {
            memcpy(m, rhs.m, 16 * sizeof(float32));
        }
        return *this;
    }

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
    friend Matrix4x4 transpose(const Matrix4x4& mat4);
    friend float32 determinant(const Matrix4x4& mat4);
    friend Matrix4x4 inverse(const Matrix4x4& mat4);
    friend Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
    friend Vec4f operator*(const Matrix4x4& mat4, const Vec4f& vev4);

    // Matrix4x4 data
    union {
        float32 m[4][4]{};  ///< Zero initialized 4x4 column major matrix
        Vec4f col[4];       ///< Each row in the matrix represents a column vector
    };
};

inline Matrix4x4 transpose(const Matrix4x4& mat4) {
    return Matrix4x4(Vec4f(mat4.m[0][0], mat4.m[1][0], mat4.m[2][0], mat4.m[3][0]),
                     Vec4f(mat4.m[0][1], mat4.m[1][1], mat4.m[2][1], mat4.m[3][1]),
                     Vec4f(mat4.m[0][2], mat4.m[1][2], mat4.m[2][2], mat4.m[3][2]),
                     Vec4f(mat4.m[0][3], mat4.m[1][3], mat4.m[2][3], mat4.m[3][3]));
}

inline float32 determinant(const Matrix4x4& m) {
    float32 result;
    // blqqqh
    result = m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] -
             m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
             m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] -
             m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
             m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] -
             m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
             m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
             m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
             m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] -
             m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
             m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
             m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
    return result;
}

// Source: https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
inline Matrix4x4 inverse(const Matrix4x4& m) {
    float32 A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
    float32 A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
    float32 A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
    float32 A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
    float32 A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
    float32 A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
    float32 A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
    float32 A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
    float32 A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
    float32 A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
    float32 A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
    float32 A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    float32 A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
    float32 A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
    float32 A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
    float32 A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
    float32 A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
    float32 A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

    const float32 det = m[0][0] * (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223) -
                        m[0][1] * (m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223) +
                        m[0][2] * (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123) -
                        m[0][3] * (m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);

    // Inverse matrix does not exist if determinant == 0
    if (fabs(det) < std::numeric_limits<float32>::epsilon())
        return m;

    float32 revDet = 1 / det;

    Matrix4x4 result;
    result[0][0] = revDet *  (m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223);
    result[0][1] = revDet * -(m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223);
    result[0][2] = revDet *  (m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213);
    result[0][3] = revDet * -(m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212);
    result[1][0] = revDet * -(m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223);
    result[1][1] = revDet *  (m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223);
    result[1][2] = revDet * -(m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213);
    result[1][3] = revDet *  (m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212);
    result[2][0] = revDet *  (m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123);
    result[2][1] = revDet * -(m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123);
    result[2][2] = revDet *  (m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113);
    result[2][3] = revDet * -(m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112);
    result[3][0] = revDet * -(m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123);
    result[3][1] = revDet *  (m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123);
    result[3][2] = revDet * -(m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113);
    result[3][3] = revDet *  (m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112);
    return result;
}

inline Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result;
    result[0] = m1.col[0] * m2.col[0][0] + m1.col[1] * m2.col[0][1] + m1.col[2] * m2.col[0][2] +
                m1.col[3] * m2.col[0][3];
    result[1] = m1.col[0] * m2.col[1][0] + m1.col[1] * m2.col[1][1] + m1.col[2] * m2.col[1][2] +
                m1.col[3] * m2.col[1][3];
    result[2] = m1.col[0] * m2.col[2][0] + m1.col[1] * m2.col[2][1] + m1.col[2] * m2.col[2][2] +
                m1.col[3] * m2.col[2][3];
    result[3] = m1.col[0] * m2.col[3][0] + m1.col[1] * m2.col[3][1] + m1.col[2] * m2.col[3][2] +
                m1.col[3] * m2.col[3][3];
    return result;
}

inline Vec4f operator*(const Matrix4x4& mat4, const Vec4f& vec4) {
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

inline std::string toString(const Matrix4x4& mat4) {
    std::stringstream stream;
    stream << "[" << toString(mat4.col[0]) << ", " << toString(mat4.col[1]) << ", "
           << toString(mat4.col[2]) << ", " << toString(mat4.col[3]) << "]";
    return stream.str();
}

}  // namespace jm

#pragma once

// Own includes
#include "math/matrix/Transform.h"

namespace jupiter {

/// @brief CRTP approach to create scene camera
template <typename DerivedCamera>
class Camera {
public:
    // Common camera setters and getters
    void setPosition(const jm::Vec3f& pos) { getDerived().setPosition(pos); }

    void setRotation(const float32 theta, const jm::Vec3f& axis = jm::Vec3f(0.f, 0.f, 1.f)) {
        getDerived().setRotation(theta, axis);
    }

    void setProjectionMatrix(const jm::Matrix4x4& projMatrix) { projectionMat = projMatrix; }
    void setViewMatrix(const jm::Matrix4x4& viewMatrix) { viewMat = viewMatrix; }

    jm::Matrix4x4 getProjectionViewMatrix() const { return getDerived().getProjectionViewMatrix(); }
    jm::Matrix4x4 getProjectionMatrix() const { return getDerived().getProjectionMatrix(); }
    jm::Matrix4x4 getViewMatrix() const { return getDerived().getViewMatrix(); }
    jm::Vec3f getPosition() const { return cameraPos; }

private:
    auto getDerived() -> DerivedCamera& { return static_cast<DerivedCamera&>(*this); }

protected:
    jm::Matrix4x4 projectionMat;
    jm::Matrix4x4 viewMat;
    jm::Vec3f cameraPos;
};

}  // namespace jupiter

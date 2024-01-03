#pragma once

// Own includes
#include "math/matrix/Transform.h"

namespace jupiter {

/// @brief CRTP approach to create scene camera
template <typename DerivedCamera>
class Camera {
public:
    Camera() = default;

    void setPosition(const jm::Vec3f& pos) { getDerived().setPosition(pos); }

    void setRotation(const float32 zRotation) { getDerived().setRotation(zRotation); }

    jm::Matrix4x4 getProjectionViewMatrix() const { return projectionMat * viewMat; }
    jm::Matrix4x4 getProjectionMatrix() const { return projectionMat; }
    jm::Matrix4x4 getViewMatrix() const { return viewMat; }
    jm::Vec3f getPosition() const { return cameraPos; }

private:
    auto getDerived() -> DerivedCamera& { return static_cast<DerivedCamera&>(*this); }

protected:
    jm::Matrix4x4 projectionMat;
    jm::Matrix4x4 viewMat;
    jm::Vec3f cameraPos;
};

}  // namespace jupiter

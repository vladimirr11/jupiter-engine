#pragma once

// Own includes
#include "cameras/BaseCamera.h"

namespace jupiter {

class OrthographicCamera : public Camera<OrthographicCamera> {
public:
    OrthographicCamera(const float32 left, const float32 right, const float32 bottom,
                       const float32 top, const float32 near = -1.f, const float32 far = 1.f) {
        projectionMat = jm::ortho(left, right, bottom, top, near, far);
    }

    void setViewport(const float32 left, const float32 right, const float32 bottom,
                     const float32 top, const float32 near = -1.f, const float32 far = 1.f) {
        projectionMat = jm::ortho(left, right, bottom, top, near, far);
    }

    void setPosition(const jm::Vec3f& pos) {
        cameraPos = -pos;
        viewMat = jm::translate(jm::Matrix4x4(), -pos);
    }

    void setRotation(const float32 zRotation, const jm::Vec3f& axis = jm::Vec3f(0.f, 0.f, 1.f)) {
        jm::Matrix4x4 transform = jm::translate(jm::Matrix4x4(), cameraPos);
        viewMat = jm::rotate(transform, -zRotation, axis);
    }

    jm::Matrix4x4 getProjectionViewMatrix() const { return projectionMat * viewMat; }
    jm::Matrix4x4 getProjectionMatrix() const { return projectionMat; }
    jm::Matrix4x4 getViewMatrix() const { return viewMat; }
};

}  // namespace jupiter

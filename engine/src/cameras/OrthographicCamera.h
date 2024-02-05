#pragma once

// Own includes
#include "cameras/BaseCamera.h"

namespace jupiter {

// Forward declarations
class MouseScrollEvent;
class WindowResizeEvent;

class OrthographicCamera : public Camera<OrthographicCamera> {
public:
    OrthographicCamera(const float32 width, const float32 height, const float32 near = -1.f,
                       const float32 far = 1.f);

    void setViewport(const float32 left, const float32 right, const float32 bottom,
                     const float32 top, const float32 near = -1.f, const float32 far = 1.f);

    void setPosition(const jm::Vec3f& pos);
    void setRotation(const float32 zRotation, const jm::Vec3f& axis = jm::Vec3f(0.f, 0.f, 1.f));

    void update(const float32 deltaTime);

    jm::Matrix4x4 getProjectionViewMatrix() const { return projectionMat * viewMat; }
    jm::Matrix4x4 getProjectionMatrix() const { return projectionMat; }
    jm::Matrix4x4 getViewMatrix() const { return viewMat; }

private:
    void onMouseScroll(const MouseScrollEvent& mouseScrollEvent);
    void onWindowResize(const WindowResizeEvent& windowResizeEvent);

private:
    float32 aspectRatio;     ///< Camera's viewport aspect ratio
    float32 zoom = 1.f;      ///< Camera's zoom level
    float32 rotation = 0.f;  ///< Keeps rotation around z-axis in degrees
};

}  // namespace jupiter

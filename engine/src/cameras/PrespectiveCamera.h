#pragma once

// Own includes
#include "cameras/BaseCamera.h"
#include "events/MouseEvents.h"
#include "events/EventManager.h"
#include "base/Input.h"

namespace jupiter {

class PrespectiveCamera : public Camera<PrespectiveCamera> {
public:
    PrespectiveCamera(const float32 fov_, const float32 width_, const float32 height_,
                      const float32 near_ = 0.1f, const float32 far_ = 100.f);

    void setViewport(const float32 fov_, const float32 viewportWidth, const float32 viewportHeight,
                     const float32 near_ = -1.f, const float32 far_ = 1.f);

    void setPosition(const jm::Vec3f& pos, const jm::Vec3f target = jm::Vec3f(0.f, 0.f, -1.f));

    // Camera orientation and field of view setters
    void setDirection(const jm::Vec3f& target) { direction = target; }
    void setFOV(const float32 fov_) { fov = fov_; }

    // Camera control setters
    void setMovementSpeed(const float32 moveSpeed) { movementSpeed = moveSpeed; }
    void setHoverSensitivity(const float32 hoverSens) { hoverSensitivity = hoverSens; }

    // Update camera position
    void update(const float32 deltaTime);

    // Recalculate each transformation matrix (if neaded) before to be used by the renderer
    jm::Matrix4x4 getProjectionViewMatrix();
    jm::Matrix4x4 getProjectionMatrix();
    jm::Matrix4x4 getViewMatrix();

private:
    void recalculateProjectionMatrix();
    void recalculateViewMatrix();

    void onMouseMove(const MouseMotionEvent& mouseMoveEvent);
    void onMouseScroll(const MouseScrollEvent& mouseScrollEvent);

private:
    jm::Vec3f direction = jm::Vec3f(0.0f, 0.0f, -1.0f);  ///< Camera's forward direction (target)
    jm::Vec3f cameraUp = jm::Vec3f(0.0f, 1.0f, 0.0f);    ///< Camera's up vector
    float32 fov = 0.f;      ///< Camera's vertical field of view in degrees
    float32 width = 0.f;    ///< Viewport width
    float32 height = 0.f;   ///< Viewport height
    float32 near = 0.1f;    ///< Camera's near clip distance
    float32 far = 100.0f;   ///< Camera's far clip distance
    bool projDirty = true;  ///< Dirty flag to indicate if projection matrix needs recalculation
    bool viewDirty = true;  ///< Dirty flag to indicate if view matrix needs recalculation
    // Camera Euler angles
    float32 pitch = 0.0f;  ///< Rotation around the x-axis
    float32 yaw = -90.f;   ///< Rotation around the y-axis
    // Camera control settings
    float32 movementSpeed = 1.5f;     ///< Camera's movement speed
    float32 hoverSensitivity = 0.05f;  ///< Mouse movement speed
};

}  // namespace jupiter

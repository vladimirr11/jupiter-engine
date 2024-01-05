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
                      const float32 near_ = 0.1f, const float32 far_ = 100.f)
        : fov(fov_), width(width_), height(height_), near(near_), far(far_), projDirty(true) {
        // Mouse event handlers
        subscribe<MouseMotionEvent>([this](const MouseMotionEvent& event) { onMouseMove(event); });
        subscribe<MouseScrollEvent>(
            [this](const MouseScrollEvent& event) { onMouseScroll(event); });
    }

    void setViewport(const float32 fov_, const float32 viewportWidth, const float32 viewportHeight,
                     const float32 near_ = -1.f, const float32 far_ = 1.f) {
        fov = fov_;
        width = viewportWidth;
        height = viewportHeight;
        near = near_;
        far = far_;
        projDirty = true;
    }

    void setPosition(const jm::Vec3f& pos, const jm::Vec3f target = jm::Vec3f(0.f, 0.f, -1.f)) {
        cameraPos = pos;
        direction = jm::normalize3(target);
        viewDirty = true;
    }

    void update(const float32 deltaTime) {
        const float32 velocity = (float32)movementSpeed * deltaTime;
        const jm::Vec3f rightDir = jm::cross(direction, cameraUp);

        if (Input::keyPressed(Keyboard::KEY_A)) {
            cameraPos -= (rightDir * velocity);
            viewDirty = true;
        } else if (Input::keyPressed(Keyboard::KEY_D)) {
            cameraPos += (rightDir * velocity);
            viewDirty = true;
        }

        if (Input::keyPressed(Keyboard::KEY_W)) {
            cameraPos += (direction * velocity);
            viewDirty = true;
        } else if (Input::keyPressed(Keyboard::KEY_S)) {
            cameraPos -= (direction * velocity);
            viewDirty = true;
        }
    }

    // Camera orientation and field of view setters
    void setDirection(const jm::Vec3f& target) { direction = target; }
    void setFOV(const float32 fov_) { fov = fov_; }

    // Camera control settings
    void setMovementSpeed(const float32 moveSpeed) { movementSpeed = moveSpeed; }
    void setHoverSensitivity(const float32 hoverSens) { hoverSensitivity = hoverSens; }

    // Recalculate each transformation matrix (if neaded) before to be used by the renderer
    jm::Matrix4x4 getProjectionViewMatrix() {
        recalculateProjectionMatrix();
        recalculateViewMatrix();
        return projectionMat * viewMat;
    }

    jm::Matrix4x4 getProjectionMatrix() {
        recalculateProjectionMatrix();
        return projectionMat;
    }
    jm::Matrix4x4 getViewMatrix() {
        recalculateViewMatrix();
        return viewMat;
    }

private:
    void recalculateProjectionMatrix() {
        if (projDirty) {
            projectionMat = jm::prespective(jm::deg2Radians(fov), width / height, near, far);
            projDirty = false;
        }
    }

    void recalculateViewMatrix() {
        if (viewDirty) {
            viewMat = jm::lookAt(cameraPos, cameraPos + direction, cameraUp);
            viewDirty = false;
        }
    }

    void onMouseMove(const MouseMotionEvent& mouseMoveEvent) {
        static bool firstMove = true;  // Is this the first move in screen
        static float32 lastXPos = width / 2;
        static float32 lastYPos = height / 2;

        // Early return if we haven't moved the mouse
        if (mouseMoveEvent.getMouseX() == lastXPos && mouseMoveEvent.getMouseY() == lastYPos) {
            return;
        }

        // We have mouse move event - recalculate the view matrix
        viewDirty = true;

        if (firstMove) {
            lastXPos = mouseMoveEvent.getMouseX();
            lastYPos = mouseMoveEvent.getMouseY();
            firstMove = false;
        }

        float32 xOffset = (mouseMoveEvent.getMouseX() - lastXPos) * hoverSensitivity;
        float32 yOffset = (lastYPos - mouseMoveEvent.getMouseY()) * hoverSensitivity;

        lastXPos = mouseMoveEvent.getMouseX();
        lastYPos = mouseMoveEvent.getMouseY();

        yaw += xOffset;
        pitch += yOffset;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        jm::Vec3f newDirection;
        newDirection.x = cos(jm::deg2Radians(yaw)) * cos(jm::deg2Radians(pitch));
        newDirection.y = sin(jm::deg2Radians(pitch));
        newDirection.z = sin(jm::deg2Radians(yaw)) * cos(jm::deg2Radians(pitch));

        // Make new camera coordinate system
        const static jm::Vec3f worldUp = jm::Vec3f(0.0f, 1.0f, 0.0f);
        direction = jm::normalize3(newDirection);
        const jm::Vec3f right = jm::normalize3(jm::cross(direction, worldUp));
        cameraUp = jm::cross(right, direction);
    }

    void onMouseScroll(const MouseScrollEvent& mouseScrollEvent) {
        static float32 zoom = fov;
        zoom -= mouseScrollEvent.getYOffset();
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;
        fov = zoom;
        projDirty = true;
    }

private:
    jm::Vec3f direction = jm::Vec3f(0.0f, 0.0f, -1.0f);  ///< Camera's forward direction (target)
    jm::Vec3f cameraUp = jm::Vec3f(0.0f, 1.0f, 0.0f);    ///< Camera's up vector
    float32 fov = 0.f;       ///< Camera's vertical field of view in degrees
    float32 width = 0.f;     ///< Viewport width
    float32 height = 0.f;    ///< Viewport height
    float32 near = 0.1f;     ///< Camera's near clip distance
    float32 far = 100.0f;    ///< Camera's far clip distance
    float32 rotation = 0.f;  ///< Rotation angle in degrees
    bool projDirty = true;   ///< Dirty flag to indicate if projection matrix needs recalculation
    bool viewDirty = true;   ///< Dirty flag to indicate if view matrix needs recalculation
    // Camera Euler angles
    float32 pitch = 0.0f;  ///< Rotation around the x-axis
    float32 yaw = -90.f;   ///< Rotation around the y-axis
    // Camera control settings
    float32 movementSpeed = 1.5f;     ///< Camera's movement speed
    float32 hoverSensitivity = 0.1f;  ///< Mouse movement speed
};

}  // namespace jupiter

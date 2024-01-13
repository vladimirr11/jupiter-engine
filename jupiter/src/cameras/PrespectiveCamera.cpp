// Jpch
#include "Jpch.h"

// Own includes
#include "cameras/PrespectiveCamera.h"

namespace jupiter {

PrespectiveCamera::PrespectiveCamera(const float32 fov_, const float32 width_,
                                     const float32 height_, const float32 near_, const float32 far_)
    : fov(fov_), width(width_), height(height_), near(near_), far(far_), projDirty(true) {
    // Mouse event handlers
    subscribe<MouseMotionEvent>([this](const MouseMotionEvent& event) { onMouseMove(event); });
    subscribe<MouseScrollEvent>([this](const MouseScrollEvent& event) { onMouseScroll(event); });
}

void PrespectiveCamera::setViewport(const float32 fov_, const float32 viewportWidth,
                                    const float32 viewportHeight, const float32 near_,
                                    const float32 far_) {
    fov = fov_;
    width = viewportWidth;
    height = viewportHeight;
    near = near_;
    far = far_;
    projDirty = true;
}

void PrespectiveCamera::setPosition(const jm::Vec3f& pos, const jm::Vec3f target) {
    cameraPos = pos;
    direction = jm::normalize3(target);
    viewDirty = true;
}

void PrespectiveCamera::update(const float32 deltaTime) {
    const float32 velocity = (float32)movementSpeed * deltaTime;
    const jm::Vec3f rightDir = jm::normalize3(jm::cross(direction, cameraUp));

    // Move camera left and right
    if (Input::keyPressed(Keyboard::KEY_A)) {
        cameraPos -= (rightDir * velocity);
        viewDirty = true;
    } else if (Input::keyPressed(Keyboard::KEY_D)) {
        cameraPos += (rightDir * velocity);
        viewDirty = true;
    }

    // Move camera forward and backward
    if (Input::keyPressed(Keyboard::KEY_W)) {
        cameraPos += (direction * velocity);
        viewDirty = true;
    } else if (Input::keyPressed(Keyboard::KEY_S)) {
        cameraPos -= (direction * velocity);
        viewDirty = true;
    }
}

jm::Matrix4x4 PrespectiveCamera::getProjectionViewMatrix() {
    recalculateProjectionMatrix();
    recalculateViewMatrix();
    return projectionMat * viewMat;
}

jm::Matrix4x4 PrespectiveCamera::getProjectionMatrix() {
    recalculateProjectionMatrix();
    return projectionMat;
}

jm::Matrix4x4 PrespectiveCamera::getViewMatrix() {
    recalculateViewMatrix();
    return viewMat;
}

void PrespectiveCamera::recalculateProjectionMatrix() {
    if (projDirty) {
        projectionMat = jm::prespective(jm::deg2Radians(fov), width / height, near, far);
        projDirty = false;
    }
}

void PrespectiveCamera::recalculateViewMatrix() {
    if (viewDirty) {
        viewMat = jm::lookAt(cameraPos, cameraPos + direction, cameraUp);
        viewDirty = false;
    }
}

void PrespectiveCamera::onMouseMove(const MouseMotionEvent& mouseMoveEvent) {
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

void PrespectiveCamera::onMouseScroll(const MouseScrollEvent& mouseScrollEvent) {
    static float32 zoom = fov;
    zoom -= mouseScrollEvent.getYOffset();
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
    fov = zoom;
    projDirty = true;
}

}  // namespace jupiter

// Jpch
#include "Jpch.h"

// Own includes
#include "cameras/OrthographicCamera.h"
#include "base/Input.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "events/EventDefines.h"
#include "events/EventManager.h"

namespace jupiter {

OrthographicCamera::OrthographicCamera(const float32 width, const float32 height,
                                       const float32 near, const float32 far)
    : aspectRatio(width / height) {
    projectionMat = jm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, near, far);
    // Subscribe camera for events
    subscribe<MouseScrollEvent>(
        [this](const MouseScrollEvent& mouseScrollEvent) { onMouseScroll(mouseScrollEvent); });
    subscribe<WindowResizeEvent>(
        [this](const WindowResizeEvent& windowResizeEvent) { onWindowResize(windowResizeEvent); });
}

void OrthographicCamera::setViewport(const float32 left, const float32 right, const float32 bottom,
                                     const float32 top, const float32 near, const float32 far) {
    projectionMat = jm::ortho(left, right, bottom, top, near, far);
    aspectRatio = (right - left) / (top - bottom);
}

void OrthographicCamera::setPosition(const jm::Vec3f& pos) {
    cameraPos = pos;
    viewMat = jm::translate(jm::Matrix4x4(), pos);
}

void OrthographicCamera::setRotation(const float32 zRotation, const jm::Vec3f& axis) {
    jm::Matrix4x4 transform = jm::translate(jm::Matrix4x4(), cameraPos);
    viewMat = jm::rotate(transform, -zRotation, axis);
}

void OrthographicCamera::update(const float32 deltaTime) {
    static constexpr float32 movementSpeed = 1.5f;
    const float32 velocity = (float32)movementSpeed * deltaTime;
    bool cameraMoved = false;

    // Move camera left and right
    if (Input::keyPressed(Keyboard::KEY_A)) {
        cameraPos.x += velocity;
        cameraMoved = true;
    } else if (Input::keyPressed(Keyboard::KEY_D)) {
        cameraPos.x -= velocity;
        cameraMoved = true;
    }

    // Move camera up and down
    if (Input::keyPressed(Keyboard::KEY_W)) {
        cameraPos.y -= velocity;
        cameraMoved = true;
    } else if (Input::keyPressed(Keyboard::KEY_S)) {
        cameraPos.y += velocity;
        cameraMoved = true;
    }

    // Rotate camera cw and acw
    if (Input::keyPressed(Keyboard::KEY_Q)) {
        rotation += velocity;
        cameraMoved = true;
    } else if (Input::keyPressed(Keyboard::KEY_E)) {
        rotation -= velocity;
        cameraMoved = true;
    }

    if (cameraMoved) {
        viewMat = jm::translate(jm::Matrix4x4(), cameraPos);
    }
    setRotation(rotation);
}

void OrthographicCamera::onMouseScroll(const MouseScrollEvent& mouseScrollEvent) {
    static constexpr float32 zoomChangeSpeed = 0.05f;
    const float32 prevFrameZoom = zoom;
    zoom -= mouseScrollEvent.getYOffset() * zoomChangeSpeed;
    if (zoom < 0.1f)
        zoom = 0.1f;
    if (zoom > 5.0f)
        zoom = 5.0f;

    if (prevFrameZoom != zoom) {
        setViewport(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
    }
}

void OrthographicCamera::onWindowResize(const WindowResizeEvent& windowResizeEvent) {
    if (windowResizeEvent.getHeight() != 0) {
        aspectRatio = windowResizeEvent.getWidth() / (float32)windowResizeEvent.getHeight();
        setViewport(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
    }
}

}  // namespace jupiter

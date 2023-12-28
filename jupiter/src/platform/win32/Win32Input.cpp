// Jpch
#include "Jpch.h"

// Own includes
#include "base/Input.h"
#include "base/Application.h"

// Third party includes
#include <GLFW/glfw3.h>

namespace jupiter {

bool Input::keyPressed(const int32 key) {
    GLFWwindow* window = (GLFWwindow*)getAppNativeWindow();
    int32 state = glfwGetKey(window, key);
    return state == GLFW_PRESS;
}

bool Input::mouseButtonPressed(const int32 mouseButton) {
    GLFWwindow* window = (GLFWwindow*)getAppNativeWindow();
    int32 state = glfwGetMouseButton(window, mouseButton);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

jm::Vec2f Input::getMousePosition() {
    GLFWwindow* window = (GLFWwindow*)getAppNativeWindow();
    float64 xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    return {(float32)xPos, (float32)yPos};
}

}  // namespace jupiter
#pragma once

// Own includes
#include "renderer/GraphicsContext.h"

// Third party includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace jupiter {

class GLContext : public GraphicsContext {
public:
    GLContext(GLFWwindow* windowHandle_);

    void init() override;
    void swapBuffers() const override;

private:
    GLFWwindow* windowHandle = nullptr;
};

}  // namespace jupiter
// Jpch
#include "Jpch.h"

// Own includes
#include "GLContext.h"
#include "base/Assert.h"

namespace jupiter {

GLContext::GLContext(GLFWwindow* windowHandle_) : windowHandle(windowHandle_) {}

void GLContext::init() {
    glfwMakeContextCurrent(windowHandle);
    // Load OpenGL function pointers
    jAssertFunc(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    JLOG_INFO("OpenGL context created");
    JLOG_INFO("OpenGL version: {}", (const char*)glGetString(GL_VERSION));
    JLOG_INFO("OpenGL renderer implementation: {}", (const char*)glGetString(GL_RENDERER));
    JLOG_INFO("OpenGL vendor implementation: {}", (const char*)glGetString(GL_VENDOR));
}

void GLContext::swapBuffers() const { glfwSwapBuffers(windowHandle); }

}  // namespace jupiter
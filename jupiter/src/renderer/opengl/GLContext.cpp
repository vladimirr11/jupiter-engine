// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLContext.h"
#include "base/Assert.h"

namespace jupiter {

GLContext::GLContext(GLFWwindow* windowHandle_) : windowHandle(windowHandle_) {}

void GLContext::init() {
    glfwMakeContextCurrent(windowHandle);
    // Load OpenGL function pointers
    jAssertFunc(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    JLOG_INFO("OpenGL context created");
    JLOG_INFO("OpenGL Vendor: {}", (const char*)getVendor());
    JLOG_INFO("OpenGL API version: {}", (const char*)getVendorVersion());
    JLOG_INFO("OpenGL renderer implementation: {}", (const char*)getRendererImplementation());
}

void GLContext::swapBuffers() const { glfwSwapBuffers(windowHandle); }

const uint8* GLContext::getVendor() const { return glGetString(GL_VENDOR); }
const uint8* GLContext::getVendorVersion() const { return glGetString(GL_VERSION); }
const uint8* GLContext::getRendererImplementation() const { return glGetString(GL_RENDERER); }

}  // namespace jupiter

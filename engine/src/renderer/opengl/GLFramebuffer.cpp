// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLFramebuffer.h"
#include "renderer/opengl/GLAssert.h"
#include "base/Assert.h"

// Third-party inludes
#include <glad/glad.h>

namespace jupiter {

GLFramebuffer::GLFramebuffer(const FramebufferConfig& config) { recreate(); }

GLFramebuffer::~GLFramebuffer() {}

void GLFramebuffer::recreate() {
    GLCALL(glGenFramebuffers(1, &fbId));
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, fbId));

    // Create color attachment texture
    GLCALL(glGenTextures(1, &colorAttachment));
    GLCALL(glBindTexture(GL_TEXTURE_2D, colorAttachment));
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fbConfig.width, fbConfig.height, 0, GL_RGBA,
                        GL_UNSIGNED_BYTE, nullptr));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                                  colorAttachment, 0));

    // Create depth attachment texture
    GLCALL(glGenTextures(1, &depthAttachment));
    GLCALL(glBindTexture(GL_TEXTURE_2D, depthAttachment));
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, fbConfig.width, fbConfig.height, 0,
                        GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
    GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                                  depthAttachment, 0));

    // Check framebuffer is complete
    jAssertExpr(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    // Unbind framebuffer
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

}  // namespace jupiter

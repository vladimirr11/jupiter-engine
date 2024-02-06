// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/Framebuffer.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLFramebuffer.h"
#endif  // GRAPHICS_API_OPENGL

namespace jupiter {

SharedPtr<Framebuffer> Framebuffer::create(const FramebufferConfig& config) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLFramebuffer>(config);
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

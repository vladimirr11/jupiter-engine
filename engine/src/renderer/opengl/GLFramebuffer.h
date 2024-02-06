#pragma once

// Own includes
#include "renderer/Framebuffer.h"

namespace jupiter {

class GLFramebuffer : public Framebuffer {
public:
    GLFramebuffer(const FramebufferConfig& config);

    ~GLFramebuffer();

    const FramebufferConfig& getConfig() const override { return fbConfig; }

private:
    void recreate();

private:
    uint32 fbId = 0u;
    uint32 colorAttachment = 0u;
    uint32 depthAttachment = 0u;
    FramebufferConfig fbConfig;
};

}  // namespace jupiter

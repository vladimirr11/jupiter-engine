#pragma once

// Own includes
#include "renderer/Framebuffer.h"

namespace jupiter {

class GLFramebuffer : public Framebuffer {
public:
    GLFramebuffer(const FramebufferConfig& config);

    ~GLFramebuffer();

    void bind() const override;
    void unbind() const override;

    void resize(const uint32 width, const uint32 height) override;
    uint32 getColorAttachmentId() const override { return colorAttachment; }

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

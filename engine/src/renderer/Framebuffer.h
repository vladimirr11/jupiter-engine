#pragma once

// Own includes
#include "base/Defines.h"

namespace jupiter {

struct FramebufferConfig {
    uint32 width = 0u;
    uint32 height = 0u;
    uint32 samples = 1u;
    bool renderOnScreen = false;
};

class Framebuffer {
public:
    virtual ~Framebuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void resize(const uint32 width, const uint32 height) = 0;
    virtual uint32 getColorAttachmentId() const = 0;

    virtual const FramebufferConfig& getConfig() const = 0;

    static SharedPtr<Framebuffer> create(const FramebufferConfig& config);
};

}  // namespace jupiter

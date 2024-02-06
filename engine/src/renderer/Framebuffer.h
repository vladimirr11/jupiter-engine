#pragma once

// Own includes
#include "base/Defines.h"

namespace jupiter {

struct FramebufferConfig {
    uint32 width = 0u;
    uint32 height = 0u;
    uint32 samples = 1u;
    bool renderOnSreen = false;
};

class Framebuffer {
public:
    virtual ~Framebuffer() = default;

    virtual const FramebufferConfig& getConfig() const = 0;

    static SharedPtr<Framebuffer> create(const FramebufferConfig& config);
};

}  // namespace jupiter

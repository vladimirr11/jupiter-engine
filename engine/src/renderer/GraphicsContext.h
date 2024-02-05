#pragma once

// Own includes
#include "base/Defines.h"

namespace jupiter {

class GraphicsContext {
public:
    ~GraphicsContext() = default;

    virtual void init() = 0;
    virtual void swapBuffers() const = 0;

    virtual const uint8* getVendor() const = 0;
    virtual const uint8* getVendorVersion() const = 0;
    virtual const uint8* getRendererImplementation() const = 0;
};

}  // namespace jupiter

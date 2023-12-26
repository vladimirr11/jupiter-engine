#pragma once

// Own includes
#include "base/Defines.h"

namespace jupiter {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setVertexData(const void* data, const uint32 numBytes) = 0;

    static SharedPtr<VertexBuffer> create(const void* data, const uint32 numBytes);
};

}  // namespace jupiter

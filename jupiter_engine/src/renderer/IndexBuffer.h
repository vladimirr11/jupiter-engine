#pragma once

// Own includes
#include "base/BaseDefines.h"

namespace jupiter {

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static SharedPtr<IndexBuffer> create(const uint32* data, const uint32 numIndices);
};

}  // namespace jupiter

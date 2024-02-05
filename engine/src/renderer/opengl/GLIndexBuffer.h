#pragma once

// Own includes
#include "renderer/IndexBuffer.h"

namespace jupiter {

class GLIndexBuffer : public IndexBuffer {
public:
    GLIndexBuffer(const uint32* data, const uint32 numIndices);

    ~GLIndexBuffer() override;

    void bind() const override;
    void unbind() const override;

    uint32 getIndicesCount() const override { return indicesCount; }

private:
    uint32 eboId = 0u;
    uint32 indicesCount = 0u;
};

}  // namespace jupiter

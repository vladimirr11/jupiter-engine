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

private:
    uint32 eboId;
};

}  // namespace jupiter

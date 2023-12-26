#pragma once

// Own includes
#include "renderer/VertexBuffer.h"

namespace jupiter {

class GLVertexBuffer : public VertexBuffer {
public:
    GLVertexBuffer(const void* data, const uint32 numBytess);

    ~GLVertexBuffer() override;

    void bind() const override;
    void unbind() const override;

    void setVertexData(const void* data, const uint32 numBytes) override;

private:
    uint32 vboId;
};

}  // namespace jupiter

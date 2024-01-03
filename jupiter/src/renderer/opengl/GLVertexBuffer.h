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

    void setBufferLayout(const VertexBufferLayout& layoutData) override { layout = layoutData; }
    const VertexBufferLayout& getLayout() const override { return layout; }

private:
    uint32 vboId;
    VertexBufferLayout layout;
};

}  // namespace jupiter

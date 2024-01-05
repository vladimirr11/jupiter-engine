#pragma once

// Own includes
#include "renderer/VertexBuffer.h"

namespace jupiter {

class GLVertexBuffer : public VertexBuffer {
public:
    GLVertexBuffer(const void* data, const uint32 numBytes_);

    ~GLVertexBuffer() override;

    void bind() const override;
    void unbind() const override;

    void setVertexData(const void* data, const uint32 numBytes) override;
    void setBufferLayout(const VertexBufferLayout& layoutData) override;

    const VertexBufferLayout& getLayout() const override { return layout; }
    uint32 getVerticesCount() const override { return numVertices; }

private:
    VertexBufferLayout layout;
    uint32 vboId = 0u;
    uint32 numBytes = 0u;
    uint32 numVertices = 0u;
};

}  // namespace jupiter

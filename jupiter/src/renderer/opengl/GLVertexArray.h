#pragma once

// C++ system includes
#include <vector>

// Own includes
#include "renderer/VertexArray.h"
#include "renderer/opengl/GLVertexBuffer.h"

namespace jupiter {

class GLVertexArray : public VertexArray {
public:
    GLVertexArray();

    ~GLVertexArray() override;

    void bind() const override;
    void unbind() const override;

    void addVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) override;
    void setIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) override;

    const SharedPtr<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }

private:
    std::vector<SharedPtr<VertexBuffer>> vertexBuffers;
    SharedPtr<IndexBuffer> indexBuffer;
    uint32 vao;
};

}  // namespace jupiter

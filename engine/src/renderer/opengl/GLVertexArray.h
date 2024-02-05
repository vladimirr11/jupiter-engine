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

    bool isIndexBufferSet() const override { return indexBufferSet; }

    const SharedPtr<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }
    const std::vector<SharedPtr<VertexBuffer>>& getVertexBuffers() const override {
        return vertexBuffers;
    }

private:
    std::vector<SharedPtr<VertexBuffer>> vertexBuffers;
    SharedPtr<IndexBuffer> indexBuffer = nullptr;
    uint32 vao = 0u;
    bool indexBufferSet = false;
};

}  // namespace jupiter

#pragma once

// Own includes
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"

namespace jupiter {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const SharedPtr<VertexBuffer>& vertexBiffer) = 0;
    virtual void setIndexBuffer(const SharedPtr<IndexBuffer>& vertexBiffer) = 0;

    virtual const SharedPtr<IndexBuffer>& getIndexBuffer() const = 0;

    static SharedPtr<VertexArray> create();
};

}  // namespace jupiter

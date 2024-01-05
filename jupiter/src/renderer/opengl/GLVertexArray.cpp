// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLVertexArray.h"
#include "base/Assert.h"

// Trird party includes
#include <glad/glad.h>

namespace jupiter {

GLVertexArray::GLVertexArray() { glGenVertexArrays(1, &vao); }
GLVertexArray::~GLVertexArray() { glDeleteVertexArrays(1, &vao); }

void GLVertexArray::bind() const { glBindVertexArray(vao); }
void GLVertexArray::unbind() const { glBindVertexArray(0); }

void GLVertexArray::addVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) {
    // Assert that the current vertex buffer has layout
    jAssertExpr(vertexBuffer->getLayout().hasLayout());

    // Bind current vao and vbo
    glBindVertexArray(vao);
    vertexBuffer->bind();

    // Lambda to convert from jupiter ShaderDataType to OpenGL basic data type
    auto shaderDataType2OpenGLDataType = [](const ShaderDataType type) -> GLenum {
        if (type == Float || type == Float2 || type == Float3 || type == Float4) {
            return GL_FLOAT;
        } else if (type == Int || type == Int2 || type == Int3 || type == Int4) {
            return GL_INT;
        }
        JLOG_ERROR("Unsupported shader data type provided: {}", (uint32)type);
        jAssertExpr(false);
        return GL_INVALID_ENUM;
    };

    // Get the vertex buffer layout and for each element in the layout configure the vertex array
    const VertexBufferLayout& layout = vertexBuffer->getLayout();
    const auto& layoutElements = layout.getLayoutElements();
    for (int32 i = 0; i < (int32)layoutElements.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, layoutElements[i].getCount(),
                              shaderDataType2OpenGLDataType(layoutElements[i].getType()),
                              layoutElements[i].isNormalized(), layout.getStride(),
                              (const void*)layoutElements[i].getOffset());
    }

    // Push current vertex buffer to the the array
    vertexBuffers.push_back(vertexBuffer);
}

void GLVertexArray::setIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer_) {
    glBindVertexArray(vao);
    indexBufferSet = true;
    indexBuffer = indexBuffer_;
    indexBuffer->bind();
}

}  // namespace jupiter

// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLVertexBuffer.h"

// Third party includes
#include <glad/glad.h>

namespace jupiter {

GLVertexBuffer::GLVertexBuffer(const void* data, const uint32 numBytes_) : numBytes(numBytes_) {
    // Prepare vbo handle
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    // Send vertex data to device memory
    glBufferData(GL_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW);
}

GLVertexBuffer::~GLVertexBuffer() { glDeleteBuffers(1, &vboId); }

void GLVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, vboId); }

void GLVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void GLVertexBuffer::setVertexData(const void* data, const uint32 numBytes_) {
    numBytes = numBytes_;
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, numBytes, data);
}

void GLVertexBuffer::setBufferLayout(const VertexBufferLayout& layoutData) {
    layout = layoutData;
    numVertices = numBytes / layout.getStride();
}

}  // namespace jupiter
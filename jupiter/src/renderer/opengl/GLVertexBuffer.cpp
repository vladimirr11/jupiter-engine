// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLVertexBuffer.h"
#include "renderer/opengl/GLAssert.h"

namespace jupiter {

GLVertexBuffer::GLVertexBuffer(const uint32 numBytes_) : numBytes(numBytes_) {
    // Prepare vbo handle
    GLCALL(glGenBuffers(1, &vboId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vboId));
    // Send vertex data to device memory
    GLCALL(glBufferData(GL_ARRAY_BUFFER, numBytes, nullptr, GL_STATIC_DRAW));
}

GLVertexBuffer::GLVertexBuffer(const void* data, const uint32 numBytes_) : numBytes(numBytes_) {
    // Prepare vbo handle
    GLCALL(glGenBuffers(1, &vboId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vboId));
    // Send vertex data to device memory
    GLCALL(glBufferData(GL_ARRAY_BUFFER, numBytes, data, GL_STATIC_DRAW));
}

GLVertexBuffer::~GLVertexBuffer() { glDeleteBuffers(1, &vboId); }

void GLVertexBuffer::bind() const { GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vboId)); }
void GLVertexBuffer::unbind() const { GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

void GLVertexBuffer::setVertexData(const void* data, const uint32 numBytes_) {
    numBytes = numBytes_;
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vboId));
    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, numBytes, data));
}

void GLVertexBuffer::setBufferLayout(const VertexBufferLayout& layoutData) {
    layout = layoutData;
    numVertices = numBytes / layout.getStride();
}

}  // namespace jupiter

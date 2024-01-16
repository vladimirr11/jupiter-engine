// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLIndexBuffer.h"
#include "renderer/opengl/GLAssert.h"

namespace jupiter {

GLIndexBuffer::GLIndexBuffer(const uint32* data, const uint32 numIndices)
    : indicesCount(numIndices) {
    // Prepare ebo handle
    GLCALL(glGenBuffers(1, &eboId));
    // Note: GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId));
    // Send vertex data to device memory
    GLCALL(
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint32), data, GL_STATIC_DRAW));
}

GLIndexBuffer::~GLIndexBuffer() { glDeleteBuffers(1, &eboId); }

void GLIndexBuffer::bind() const { GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId)); }

void GLIndexBuffer::unbind() const { GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

}  // namespace jupiter

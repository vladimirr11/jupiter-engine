// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLIndexBuffer.h"

// Third party includes
#include <glad/glad.h>

namespace jupiter {

GLIndexBuffer::GLIndexBuffer(const uint32* data, const uint32 numIndices)
    : indicesCount(numIndices) {
    // Prepare ebo handle
    glGenBuffers(1, &eboId);
    // Note: GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    // Send vertex data to device memory
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint32), data, GL_STATIC_DRAW);
}

GLIndexBuffer::~GLIndexBuffer() { glDeleteBuffers(1, &eboId); }

void GLIndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); }

void GLIndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

}  // namespace jupiter

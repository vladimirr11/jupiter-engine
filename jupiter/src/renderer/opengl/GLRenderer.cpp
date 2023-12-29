// Jpch
#include "Jpch.h"

// Onw includes
#include "renderer/opengl/GLRenderer.h"

// Third party includes
#include <glad/glad.h>

namespace jupiter {

GLRenderer::~GLRenderer() {}

void GLRenderer::init() const {}

void GLRenderer::shutDown() const {}

void GLRenderer::clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void GLRenderer::setClearColor(const jm::Vec4f& color) const {
    glClearColor(color.x, color.y, color.z, color.w);
}

void GLRenderer::drawElements(const SharedPtr<VertexArray>& vertArray) const {
    vertArray->bind();
    glDrawElements(GL_TRIANGLES, vertArray->getIndexBuffer()->getIndicesCount(), GL_UNSIGNED_INT,
                   nullptr);
}

}  // namespace jupiter
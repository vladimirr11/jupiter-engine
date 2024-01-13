// Jpch
#include "Jpch.h"

// Onw includes
#include "renderer/opengl/GLRenderer.h"

// Third party includes
#include <glad/glad.h>

namespace jupiter {

GLRenderer::~GLRenderer() {}

void GLRenderer::init() const {
    // Enable alpha transparency on renderer init
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLRenderer::shutDown() const {}

void GLRenderer::clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void GLRenderer::setClearColor(const jm::Vec4f& color) const {
    glClearColor(color.x, color.y, color.z, color.w);
}

void GLRenderer::setViewport(const float32 width, const float32 height) const {
    glViewport(0, 0, width, height);
}

void GLRenderer::drawElements(const SharedPtr<VertexArray>& vertArray) const {
    vertArray->bind();
    if (vertArray->isIndexBufferSet()) {
        glDrawElements(GL_TRIANGLES, vertArray->getIndexBuffer()->getIndicesCount(),
                       GL_UNSIGNED_INT, nullptr);
    } else {
        uint32 numVertices = 0u;
        for (uint64 i = 0; i < vertArray->getVertexBuffers().size(); i++) {
            numVertices += vertArray->getVertexBuffers()[i]->getVerticesCount();
        }
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
    }
}

}  // namespace jupiter
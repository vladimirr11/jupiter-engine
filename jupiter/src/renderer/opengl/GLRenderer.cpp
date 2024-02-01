// Jpch
#include "Jpch.h"

// Onw includes
#include "renderer/opengl/GLRenderer.h"
#include "renderer/opengl/GLAssert.h"

namespace jupiter {

GLRenderer::~GLRenderer() {}

void GLRenderer::init() const {
    // Enable alpha transparency on renderer init
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void GLRenderer::shutDown() const {}

void GLRenderer::clear() const { GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }
void GLRenderer::setClearColor(const jm::Vec4f& color) const {
    GLCALL(glClearColor(color.x, color.y, color.z, color.w));
}

void GLRenderer::setViewport(const uint32 width, const uint32 height) const {
    GLCALL(glViewport(0, 0, width, height));
}

void GLRenderer::drawElements(const SharedPtr<VertexArray>& vertArray, const uint32 indices) const {
    vertArray->bind();
    if (indices) { // Draw call if we use batch rendering
        GLCALL(glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, nullptr));
        return;
    }

    // If we use instance rendering
    if (vertArray->isIndexBufferSet()) {
        GLCALL(glDrawElements(GL_TRIANGLES, vertArray->getIndexBuffer()->getIndicesCount(),
                              GL_UNSIGNED_INT, nullptr));
    } else {
        uint32 numVertices = 0u;
        for (uint64 i = 0; i < vertArray->getVertexBuffers().size(); i++) {
            numVertices += vertArray->getVertexBuffers()[i]->getVerticesCount();
        }
        GLCALL(glDrawArrays(GL_TRIANGLES, 0, numVertices));
    }
}

}  // namespace jupiter

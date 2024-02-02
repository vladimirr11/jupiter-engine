#pragma once

// Own includes
#include "renderer/RendererBackend.h"
#include "renderer/BatchRenderer.h"
#include "cameras/BaseCamera.h"

namespace jupiter {

class Renderer {
public:
    // Helper methods for 2D and 3D rendering
    struct Command {
        static void clear() { renderBackend->clear(); }
        static void setClearColor(const jm::Vec4f& color) { renderBackend->setClearColor(color); }

        static void setViewport(const uint32 width, const uint32 height) {
            renderBackend->setViewport(width, height);
        }

        static void drawElements(const SharedPtr<VertexArray>& vertArray,
                                 const uint32 indices = 0) {
            renderBackend->drawElements(vertArray, indices);
        }

        static void drawQuad(const QuadDescription& quadDescr) {
            BatchRenderer::drawQuad(quadDescr);
        }
    };

    // Render statistics
    struct Statistics {
        static uint32 getDrawCalls() { return BatchRenderer::getStat().drawCalls; }
        static uint32 getDrawQuads() { return BatchRenderer::getStat().drawQuads; }
        static uint32 getDrawVertices() { return BatchRenderer::getStat().drawVertices; }
    };

public:
    // Public API of the 3D Randerer
    static void init() {
        renderBackend->init();
        BatchRenderer::init();
    }

    static void shutDown() { renderBackend->shutDown(); }

    template <typename CameraType>
    static void beginFrame(SharedPtr<CameraType> camera) {
        sceneData.projViewMatrix = camera->getProjectionViewMatrix();
        BatchRenderer::beginBatch();
    }

    // Used for instance rendering
    static void render(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertArray,
                       const jm::Matrix4x4& modelTransform = jm::Matrix4x4()) {
        shader->bind();
        shader->setUniformMat4x4f("projViewMatrix", sceneData.projViewMatrix);
        shader->setUniformMat4x4f("modelTransform", modelTransform);
        Renderer::Command::drawElements(vertArray);
    }

    // Used for batch rendering
    static void render(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertArray,
                       const uint32 indices) {
        shader->bind();
        shader->setUniformMat4x4f("projViewMatrix", sceneData.projViewMatrix);
        Renderer::Command::drawElements(vertArray, indices);
    }

    static void finishFrame() { BatchRenderer::flushBatch(); }

private:
    struct SceneData {
        jm::Matrix4x4 projViewMatrix;
    };

private:
    inline static UniquePtr<RendererBackend> renderBackend = RendererBackend::create();
    inline static SceneData sceneData;
};

}  // namespace jupiter

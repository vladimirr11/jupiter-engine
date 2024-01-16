#pragma once

// Own includes
#include "renderer/RendererBackend.h"
#include "renderer/PrimitiveRenderer.h"
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

        static void drawElements(const SharedPtr<VertexArray>& vertArray) {
            renderBackend->drawElements(vertArray);
        }

        static void set2DConfig(const Renderer2DConfigData& config) {
            PrimitiveRenderer::attach2DConfigData(config);
        }

        static void drawQuad(const Quad& quadDescr) { PrimitiveRenderer::drawQuad(quadDescr); }
    };

public:
    // Public API of the 3D Randerer
    static void init() {
        renderBackend->init();
        PrimitiveRenderer::init();
    }

    static void shutDown() {
        renderBackend->shutDown();
        PrimitiveRenderer::shutDown();
    }

    template <typename CameraType>
    static void beginFrame(SharedPtr<CameraType> camera) {
        sceneData.projViewMatrix = camera->getProjectionViewMatrix();
    }

    static void render(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertArray,
                       const jm::Matrix4x4& modelTransform = jm::Matrix4x4()) {
        shader->bind();
        shader->setUniformMat4x4f("projViewMatrix", sceneData.projViewMatrix);
        shader->setUniformMat4x4f("modelTransform", modelTransform);
        Renderer::Command::drawElements(vertArray);
    }

    static void finishFrame() {}

private:
    struct SceneData {
        jm::Matrix4x4 projViewMatrix;
    };

private:
    inline static UniquePtr<RendererBackend> renderBackend = RendererBackend::create();
    inline static SceneData sceneData;
};

}  // namespace jupiter

#pragma once

// Own includes
#include "renderer/RendererBackend.h"
#include "renderer/Shader.h"
#include "cameras/BaseCamera.h"

namespace jupiter {

class Renderer {
public:
    struct Command {
        static void clear() { renderBackend->clear(); }

        static void setClearColor(const jm::Vec4f& color) { renderBackend->setClearColor(color); }

        static void drawElements(const SharedPtr<VertexArray>& vertArray) {
            renderBackend->drawElements(vertArray);
        }

        static void setViewport(const float32 width, const float32 height) {
            renderBackend->setViewport(width, height);
        }
    };

public:
    // Public frontend of the Randerer
    static void init() { renderBackend->init(); }
    static void shutDown() { renderBackend->shutDown(); }

    template <typename CameraType>
    static void beginFrame(SharedPtr<CameraType> camera) {
        renderData.projViewMatrix = camera->getProjectionViewMatrix();
    }

    static void render(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertArray,
                       const jm::Matrix4x4& modelTransform = jm::Matrix4x4()) {
        shader->bind();
        shader->setUniformMat4x4f(renderData.projViewMatrixName, renderData.projViewMatrix);
        shader->setUniformMat4x4f(renderData.modelTransformMatrixName, modelTransform);
        Renderer::Command::drawElements(vertArray);
    }

    static void finishFrame() {}

private:
    struct RenderData {
        jm::Matrix4x4 projViewMatrix;
        std::string projViewMatrixName;
        std::string modelTransformMatrixName;
    };

private:
    inline static UniquePtr<RendererBackend> renderBackend = RendererBackend::create();
    inline static RenderData renderData =
        RenderData(jm::Matrix4x4(), "projViewMatrix", "modelTransform");
};

}  // namespace jupiter

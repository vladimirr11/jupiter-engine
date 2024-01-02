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

        static void drwaElements(const SharedPtr<VertexArray>& vertArray) {
            renderBackend->drawElements(vertArray);
        }
    };

public:
    // Public frontend of the Randerer
    static void init() { renderBackend->init(); }
    static void shutDown() { renderBackend->shutDown(); }

    template <typename CameraType>
    static void beginFrame(SharedPtr<CameraType> camera) {
        projViewMatrix = camera->getProjectionViewMatrix();
    }

    static void render(const SharedPtr<Shader>& shader, const SharedPtr<VertexArray>& vertArray) {
        shader->bind();
        shader->setUniformMat4x4f("projViewMatrix", projViewMatrix);
        Renderer::Command::drwaElements(vertArray);
    }

    static void finishFrame() {}

private:
    inline static UniquePtr<RendererBackend> renderBackend = RendererBackend::create();
    inline static jm::Matrix4x4 projViewMatrix = jm::Matrix4x4();
};

}  // namespace jupiter

#pragma once

// Own includes
#include "renderer/RendererBackend.h"

namespace jupiter {

class RenderCommand {
public:
    static void init() { renderBackend->init(); }

    static void shutDown() { renderBackend->shutDown(); }

    static void clear() { renderBackend->clear(); }

    static void setClearColor(const jm::Vec4f& color) { renderBackend->setClearColor(color); }

    static void drwaElements(const SharedPtr<VertexArray>& vertArray) {
        renderBackend->drawElements(vertArray);
    }

private:
    inline static UniquePtr<RendererBackend> renderBackend = RendererBackend::create();
};

}  // namespace jupiter

#pragma once

// Own includes
#include "renderer/RendererBackend.h"

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

private:
    inline static UniquePtr<RendererBackend> renderBackend = RendererBackend::create();
};

}  // namespace jupiter

#pragma once

// Own includes
#include "scene/primitives/2DPrimitives.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"

namespace jupiter {

struct PrimitiveRenderConfig {
    SharedPtr<Shader> shader = nullptr;
    std::vector<SharedPtr<Texture>> textures;
    SharedPtr<VertexArray> vertexArray;
};

struct Renderer2DConfigData {
    PrimitiveRenderConfig quadData;
};

class PrimitivesRenderer {
public:
    static void init();  // Init default config
    static void shutDown();

    static void attach2DConfigData(const Renderer2DConfigData& config) {}  // Change default config
    // Render methods
    static void drawQuad(const QuadDescription& quadDescr);

private:
    inline static Renderer2DConfigData r2dConfig;
};

}  // namespace jupiter

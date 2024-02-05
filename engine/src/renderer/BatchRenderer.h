#pragma once

// C++ system includes
#include <array>

// Own includes
#include "scene/primitives/2DPrimitives.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"

namespace jupiter {

struct PrimitiveRenderData {
    SharedPtr<Shader> shader = nullptr;
    SharedPtr<VertexArray> vertexArray = nullptr;
    SharedPtr<VertexBuffer> vertexBuffer = nullptr;
    uint32 verticesCount = 0u;
    uint32 indicesCount = 0u;
};

struct BatchRenderData {
    // Quad data
    PrimitiveRenderData quad;
    SharedArrPtr<QuadVertex> quadVertexBatch;
    // Textures
    std::array<SharedPtr<Texture2D>, 32> textures;
    int32 usedSlots = 0;
};

class BatchRenderer {
private:
    struct Statistics {
        uint32 drawCalls = 0u;
        uint32 drawQuads = 0u;
        uint32 drawVertices = 0u;
    };

public:
    static void init();

    static void beginBatch();
    static void flushBatch();

    static void drawQuad(const QuadDescription& quadDescr);

    static Statistics getStat() { return stats; }

private:
    inline static BatchRenderData renderData;
    inline static Statistics stats;
};

}  // namespace jupiter

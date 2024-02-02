// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/Renderer.h"
#include "math/matrix/Transform.h"

namespace jupiter {

constexpr uint64 kMaxQuads = 10'000;
constexpr uint64 kMaxQuadVertices = kMaxQuads * 4;
constexpr uint64 kMaxQuadIndices = kMaxQuads * 6;
constexpr uint64 kMaxTextureSlots = 32;

void BatchRenderer::init() {
    // Create default quad shader program
    const FilesysPath vsPath = "../jupiter/assets/shaders/BatchRenderShader.vert";
    const FilesysPath fsPath = "../jupiter/assets/shaders/BatchRenderShader.frag";
    renderData.quad.shader = Shader::create(vsPath, fsPath);

    // Create quad vertex and index batch
    renderData.quadVertexBatch = newSharedArrPtr<QuadVertex>(kMaxQuadVertices);
    SharedArrPtr<uint32> quadIndexBatch = newSharedArrPtr<uint32>(kMaxQuadIndices);

    // Populate the index batch
    uint32 offset = 0;
    for (uint64 i = 0; i < kMaxQuadIndices; i += 6) {
        quadIndexBatch[i + 0] = offset + 0;
        quadIndexBatch[i + 1] = offset + 1;
        quadIndexBatch[i + 2] = offset + 2;
        quadIndexBatch[i + 3] = offset + 2;
        quadIndexBatch[i + 4] = offset + 3;
        quadIndexBatch[i + 5] = offset + 0;
        offset += 4;
    }

    // Create quad vao, vbo, and ebo
    renderData.quad.vertexArray = VertexArray::create();
    renderData.quad.vertexBuffer = VertexBuffer::create(kMaxQuadVertices * sizeof(QuadVertex));
    SharedPtr<IndexBuffer> quadEb = IndexBuffer::create(quadIndexBatch.get(), kMaxQuadIndices);

    VertexBufferLayout quadVbLayout{VertexDataType::Float4, VertexDataType::Float4,
                                    VertexDataType::Float2, VertexDataType::Float,
                                    VertexDataType::Float};

    renderData.quad.vertexBuffer->setBufferLayout(quadVbLayout);
    renderData.quad.vertexArray->addVertexBuffer(renderData.quad.vertexBuffer);
    renderData.quad.vertexArray->setIndexBuffer(quadEb);

    // Create default white texture
    SharedPtr<Texture2D> whiteTexture = Texture2D::createWhite();
    renderData.textures[0] = whiteTexture;
    renderData.usedSlots++;

    // Upload texture samplers array to the GPU
    int32 samplers[kMaxTextureSlots];
    for (int32 i = 0; i < kMaxTextureSlots; i++) {
        samplers[i] = i;
    }
    renderData.quad.shader->bind();
    renderData.quad.shader->setUniformIntArray("uSampler", samplers, kMaxTextureSlots);
}

void BatchRenderer::beginBatch() {
    renderData.quad.verticesCount = 0u;
    renderData.quad.indicesCount = 0u;
    // Reset stats
    stats.drawCalls = 0u;
    stats.drawQuads = 0u;
    stats.drawVertices = 0u;
}

void BatchRenderer::flushBatch() {
    if (renderData.quad.indicesCount) {
        // Send dynamic vertex data for rendering each frame
        auto bufferData = renderData.quadVertexBatch.get();
        auto bufferBytes = renderData.quad.verticesCount * sizeof(QuadVertex);
        renderData.quad.vertexBuffer->setVertexData(bufferData, bufferBytes);

        // Bind occupied texture slots
        for (uint32 i = 0; i < (uint32)renderData.textures.size(); i++) {
            if (renderData.textures[i]) {
                renderData.textures[i]->bind(i);
            }
        }

        // Render
        Renderer::render(renderData.quad.shader, renderData.quad.vertexArray,
                         renderData.quad.indicesCount);

        // Get stats
        stats.drawCalls++;
    }

    renderData.quad.verticesCount = 0u;
    renderData.quad.indicesCount = 0u;
    renderData.usedSlots = 1;  // We have reserved place for the white texture at slot 0
}

void BatchRenderer::drawQuad(const QuadDescription& quadDescr) {
    // Unit quad position and texture coordinates
    static const jm::Vec4f unitQuadPositions[] = {{-0.5f, -0.5f, 0.0f, 1.0f},
                                                  {0.5f, -0.5f, 0.0f, 1.0f},
                                                  {0.5f, 0.5f, 0.0f, 1.0f},
                                                  {-0.5f, 0.5f, 0.0f, 1.0f}};
    static const jm::Vec2f unitQuadTexCoords[] = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

    if (renderData.usedSlots >= kMaxTextureSlots ||
        renderData.quad.verticesCount >= kMaxQuadVertices) {
        flushBatch();
    }

    // Get model transform matrix
    jm::Matrix4x4 transform;
    jm::Matrix4x4 pos = jm::translate(jm::Matrix4x4(), quadDescr.position);
    jm::Matrix4x4 scale = jm::scale(jm::Matrix4x4(), jm::Vec3f(quadDescr.size, 0.f));
    if (quadDescr.rotation > 0.f) {
        jm::Matrix4x4 rot = jm::rotate(jm::Matrix4x4(), jm::deg2Radians(quadDescr.rotation),
                                       jm::Vec3f(0.f, 0.f, 1.f));
        transform = pos * rot * scale;
    } else {
        transform = pos * scale;
    }

    // If quad has texture - set it up
    int32 texSlot = 0;
    if (quadDescr.texture) {
        int32& currSlot = renderData.usedSlots;
        texSlot = currSlot;
        renderData.textures[currSlot++] = quadDescr.texture;
    }

    // Transform each quad vertex
    constexpr uint32 numQuadVertices = 4;
    const uint32 currVertex = renderData.quad.verticesCount;
    for (uint32 i = 0; i < numQuadVertices; i++) {
        renderData.quadVertexBatch[currVertex + i].position = transform * unitQuadPositions[i];
        renderData.quadVertexBatch[currVertex + i].color = quadDescr.color;
        renderData.quadVertexBatch[currVertex + i].texCoords = unitQuadTexCoords[i];
        renderData.quadVertexBatch[currVertex + i].texScaler = quadDescr.texScaler;
        renderData.quadVertexBatch[currVertex + i].texSlot = texSlot;
        renderData.quad.verticesCount++;
    }
    renderData.quad.indicesCount += 6;

    // Get stats 
    stats.drawQuads++;
    stats.drawVertices += numQuadVertices;
}

}  // namespace jupiter

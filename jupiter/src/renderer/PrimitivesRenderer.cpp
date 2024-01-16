// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "renderer/IndexBuffer.h"
#include "math/matrix/Transform.h"

namespace jupiter {

void PrimitivesRenderer::init() {
    // Default vertex data
    float32 vertices[] = {0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   // top right
                          0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
                          -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
                          -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};  // top left

    // Indices data
    uint32 indices[] = {0, 1, 3, 1, 2, 3};

    // Create vertex array
    r2dConfig.quadData.vertexArray = VertexArray::create();

    // Create index buffer
    SharedPtr<IndexBuffer> ebo = IndexBuffer::create(indices, (uint32)std::size(indices));

    // Create shader program
    const FilesysPath vsPath = "../assets/shaders/DefaultTexture.vert";
    const FilesysPath fsPath = "../assets/shaders/DefaultTexture.frag";
    r2dConfig.quadData.shader = Shader::create(vsPath, fsPath);

    // Create textures
    SharedPtr<Texture2D> texture1 = Texture2D::create("../assets/textures/Checkerboard.png");
    SharedPtr<Texture2D> texture2 = Texture2D::create("../assets/textures/Dices.png");
    r2dConfig.quadData.textures.push_back(texture1);
    r2dConfig.quadData.textures.push_back(texture2);

    r2dConfig.quadData.shader->bind();
    r2dConfig.quadData.shader->setUniformInt("uTextureSampler", 0);  // 0 indicates the texture slot
    r2dConfig.quadData.shader->unbind();

    // Create vertex buffer and set default layout
    SharedPtr<VertexBuffer> vbo = VertexBuffer::create(vertices, sizeof(vertices));
    VertexBufferLayout vboLayout{VertexDataType::Float3, VertexDataType::Float2};
    vbo->setBufferLayout(vboLayout);

    // Add vbo and ebo to vao
    r2dConfig.quadData.vertexArray->addVertexBuffer(vbo);
    r2dConfig.quadData.vertexArray->setIndexBuffer(ebo);

    r2dConfig.quadData.vertexArray->unbind();
    vbo->unbind();
}

void PrimitivesRenderer::shutDown() {}

void PrimitivesRenderer::drawQuad(const Quad& quadDescr) {
    // Set tranformation matrix and render that quad for each attached texture (if any)
    jm::Matrix4x4 pos = jm::translate(jm::Matrix4x4(), quadDescr.position);
    jm::Matrix4x4 scale = jm::scale(jm::Matrix4x4(), quadDescr.size);
    jm::Matrix4x4 transform = pos * scale;
    for (const auto& texture : r2dConfig.quadData.textures) {
        texture->bind();
        Renderer::render(r2dConfig.quadData.shader, r2dConfig.quadData.vertexArray, transform);
    }
}

}  // namespace jupiter

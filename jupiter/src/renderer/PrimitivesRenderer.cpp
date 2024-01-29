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
    const FilesysPath vsPath = "assets/shaders/DefaultTextureShader.vert";
    const FilesysPath fsPath = "assets/shaders/DefaultTextureShader.frag";
    r2dConfig.quadData.shader = Shader::create(vsPath, fsPath);

    // Create textures
    SharedPtr<Texture2D> texture1 = Texture2D::create("assets/textures/Checkerboard.png");
    r2dConfig.quadData.textures.push_back(texture1);
    //SharedPtr<Texture2D> texture2 = Texture2D::create("assets/textures/Dices.png");
    //r2dConfig.quadData.textures.push_back(texture2);

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

void PrimitivesRenderer::drawQuad(const QuadDescription& quadDescr) {
    jm::Matrix4x4 transform;
    jm::Matrix4x4 pos = jm::translate(jm::Matrix4x4(), quadDescr.position);
    jm::Matrix4x4 scale = jm::scale(jm::Matrix4x4(), quadDescr.size);
    if (quadDescr.rotation > 0.f) {
        jm::Matrix4x4 rot = jm::rotate(jm::Matrix4x4(), jm::deg2Radians(quadDescr.rotation),
                                       jm::Vec3f(0.f, 0.f, 1.f));
        transform = pos * rot * scale;
    } else {
        transform = pos * scale;
    }

    r2dConfig.quadData.shader->bind();
    r2dConfig.quadData.shader->setUniformInt("uTexScaler", quadDescr.texScaler);
    r2dConfig.quadData.shader->setUniformVec4f("uColor", quadDescr.color);

    if (!quadDescr.useTexture) {  // Render without texture
        r2dConfig.quadData.shader->setUniformInt("uTexFlag", 0);
        Renderer::render(r2dConfig.quadData.shader, r2dConfig.quadData.vertexArray, transform);
        return;
    }

    r2dConfig.quadData.shader->setUniformInt("uTexFlag", 1);
    for (const auto& texture : r2dConfig.quadData.textures) {  // Render with texture
        texture->bind();
        Renderer::render(r2dConfig.quadData.shader, r2dConfig.quadData.vertexArray, transform);
    }
}

}  // namespace jupiter

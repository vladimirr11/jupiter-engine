// C++ system includes
#include <cstdint>

// Jupiter includes
#include <Jupiter.h>

// Third-party includes
#include <imgui/imgui.h>

using namespace jupiter;

class DemoJupiterApp2d : public jupiter::Application {
public:
    DemoJupiterApp2d() { init(); }

    ~DemoJupiterApp2d() override { shutDown(); }

private:
    void init() override {
        const std::string vertexShaderSource = R"(
        #version 450 core
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec2 texCoord;
        
        uniform mat4 projViewMatrix;
        uniform mat4 modelTransform;
        
        out vec2 vTexCoord;
        void main() {
            gl_Position = projViewMatrix * modelTransform * vec4(pos.x, pos.y, pos.z, 1.0);
            vTexCoord = texCoord;
        }
)";

        const std::string fragmentShaderSource = R"(
        #version 450 core
        
        uniform sampler2D uTextureSampler;
        in vec2 vTexCoord; 

        out vec4 fragColor;

        void main() {
            fragColor = texture(uTextureSampler, vTexCoord);
        }
)";

        // Vertex data
        float32 vertices[] = {0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   // top right
                              0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
                              -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
                              -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};  // top left

        // Indices data
        uint32 indices[] = {0, 1, 3, 1, 2, 3};

        // Create shader program, vbo, vao, and ebo
        shader = Shader::create(vertexShaderSource, fragmentShaderSource);
        vbo = VertexBuffer::create(vertices, sizeof(vertices));
        ebo = IndexBuffer::create(indices, std::size(indices));
        vao = VertexArray::create();

        // Create textures
        texture1 = Texture2D::create("2dsandbox/assets/Checkerboard.png");
        texture2 = Texture2D::create("2dsandbox/assets/Dices.png");

        shader->bind();
        shader->setUniformInt("uTextureSampler", 0);  // 0 indicates the texture slot
        shader->unbind();

        // Set vertex buffer layout
        VertexBufferLayoutData posData(ShaderDataType::Float3);
        VertexBufferLayoutData texData(ShaderDataType::Float2);
        VertexBufferLayout bufferLayout;
        bufferLayout.update(posData);
        bufferLayout.update(texData);
        vbo->setBufferLayout(bufferLayout);

        // Add vbo and ebo to vao
        vao->addVertexBuffer(vbo);
        vao->setIndexBuffer(ebo);

        // Unbind vba and vbo
        vao->unbind();
        vbo->unbind();

        // Create ortho camera with defined viewport and position
        camera = newSharedPtr<OrthographicCamera>(-1.f, 1.f, -1.f, 1.f);
        camera->setPosition(jm::Vec3f(.0f, .0f, .0f));
    }

    void update(const float32 deltaTime) override {
        // Update camera position in the scene wrt to delta time
        camera->update(deltaTime);

        // Clear frame
        Renderer::Command::setClearColor(jm::Vec4f(0.45f, 0.55f, 0.60f, 1.00f));
        Renderer::Command::clear();

        // Set scene camera
        Renderer::beginFrame(camera);

        // Bind texture1 and render
        texture1->bind();
        Renderer::render(shader, vao, jm::Matrix4x4());

        // Bind texture2 and render on top of texture1
        texture2->bind();
        Renderer::render(shader, vao, jm::Matrix4x4());

        // Doesn't do anything for now
        Renderer::finishFrame();
    }

    void uiLayerUpdate() override {
        // Set tringle color
        // ImGui::Begin("Color Settings");
        // ImGui::ColorEdit3("Triangle Color", &triangleColor[0]);
        // ImGui::End();

        //// Send color to the device
        // shader->bind();
        // shader->setUniformVec3f("myColor", triangleColor);
        // shader->unbind();
    }

    void shutDown() override {}

private:
    SharedPtr<Shader> shader = nullptr;
    SharedPtr<VertexBuffer> vbo = nullptr;
    SharedPtr<IndexBuffer> ebo = nullptr;
    SharedPtr<VertexArray> vao = nullptr;
    SharedPtr<Texture2D> texture1 = nullptr;
    SharedPtr<Texture2D> texture2 = nullptr;
    SharedPtr<OrthographicCamera> camera = nullptr;

    jm::Vec3f triangleColor = jm::Vec3f(1.0f, 0.5f, 0.2f);
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp2d(); }

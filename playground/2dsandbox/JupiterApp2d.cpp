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
        
        //out vec2 vTexCoord;            
        void main() {
            gl_Position = projViewMatrix * modelTransform * vec4(pos.x, pos.y, pos.z, 1.0);
            //vTexCoord = texCoord;
        }
)";

        const std::string fragmentShaderSource = R"(
        #version 450 core
        
        //uniform sampler2D uTexture;
        //in vec2 vTexCoord; 
        
        uniform vec3 myColor;
        out vec4 fragColor;

        void main() {
            //fragColor = texture(uTexture, vTexCoord);
            fragColor = vec4(myColor, 1.0);
        }
)";

        // Vertex data
        float32 vertices[] = {0.5f,  0.5f,  0.0f, 1.0f, 1.0f,   // top right
                              0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
                              -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
                              -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};  // top left;

        // Indices data
        uint32 indices[] = {0, 1, 3, 1, 2, 3};

        // Create shader program, vbo, vao, ebo, and test texture
        shader = Shader::create(vertexShaderSource, fragmentShaderSource);
        vbo = VertexBuffer::create(vertices, sizeof(vertices));
        ebo = IndexBuffer::create(indices, std::size(indices));
        vao = VertexArray::create();
        texture = Texture2D::create(
            "C:/Users/user/source/jupiter_engine/playground/2dsandbox/assets/DemoTexture.png");

        // Set uniform color
         shader->bind();
         shader->setUniformVec3f("myColor", triangleColor);
         shader->unbind();

        //shader->bind();
        //shader->setUniformInt("uTexture", 0);  // 0 indicates sthe texture slot
        //shader->unbind();

        // Set vertex buffer layout
        VertexBufferLayoutData posData(ShaderDataType::Float3);
        VertexBufferLayoutData texData(ShaderDataType::Float2);
        VertexBufferLayout bufferLayout;
        bufferLayout.update(posData);
        bufferLayout.update(texData);
        vbo->setBufferLayout(bufferLayout);

        // Add vbo and ebo to the vao
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

        jm::Matrix4x4 scale = jm::scale(jm::Matrix4x4(), jm::Vec3f(.5f));
        Renderer::render(shader, vao, scale);

        // Doesn't do anything for now
        Renderer::finishFrame();
    }

    void uiLayerUpdate() override {
        // Set tringle color
        ImGui::Begin("Color Settings");
        ImGui::ColorEdit3("Triangle Color", &triangleColor[0]);
        ImGui::End();

        // Send color to the device
        shader->bind();
        shader->setUniformVec3f("myColor", triangleColor);
        shader->unbind();
    }

    void shutDown() override {}

private:
    SharedPtr<Shader> shader = nullptr;
    SharedPtr<VertexBuffer> vbo = nullptr;
    SharedPtr<IndexBuffer> ebo = nullptr;
    SharedPtr<VertexArray> vao = nullptr;
    SharedPtr<Texture2D> texture = nullptr;
    SharedPtr<OrthographicCamera> camera = nullptr;

    jm::Vec3f triangleColor = jm::Vec3f(1.0f, 0.5f, 0.2f);
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp2d(); }

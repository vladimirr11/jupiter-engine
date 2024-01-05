// C++ system includes
#include <cstdint>
#include <iostream>

// Jupiter includes
#include <Jupiter.h>

using namespace jupiter;

class DemoJupiterApp3d : public jupiter::Application {
public:
    DemoJupiterApp3d() { init(); }

    ~DemoJupiterApp3d() override { shutDown(); }

private:
    void init() override {
        const std::string vertexShaderSource = R"(
        #version 410 core
        layout (location = 0) in vec3 pos;
        
        uniform vec4 cubeColor;
        uniform mat4 projViewMatrix;
        uniform mat4 modelTransform;

        out vec4 ourColor;
        void main() {
            gl_Position = projViewMatrix * modelTransform * vec4(pos.x, pos.y, pos.z, 1.0);
            ourColor = cubeColor;
        }
)";

        const std::string fragmentShaderSource = R"(
        #version 410 core
        in vec4 ourColor;

        out vec4 fragColor;
        void main() {
            fragColor = ourColor;
        }
)";

        // 3D cube vertex data - 36 vertices
        float32 vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f,
            -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,
            0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f,
            0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f,
            0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};

        // Create shader program
        shader = Shader::create(vertexShaderSource, fragmentShaderSource);
        shader->bind();
        shader->setUniformVec4f("cubeColor", jm::Vec4f(1.0f, 0.5f, 0.2f, 1.0f));

        // Create vbo and vao
        vbo = VertexBuffer::create(vertices, sizeof(vertices));
        vao = VertexArray::create();

        // Set vertex buffer layout
        VertexBufferLayoutData posData(ShaderDataType::Float3);
        VertexBufferLayout bufferLayout;
        bufferLayout.update(posData);
        vbo->setBufferLayout(bufferLayout);

        // Add vbo to vao
        vao->addVertexBuffer(vbo);

        // Unbind vba and vbo
        vao->unbind();
        vbo->unbind();

        // Create prespective camera
        const Window& window = Application::getWindow();
        camera = newSharedPtr<PrespectiveCamera>(45.f, window.getWidth(), window.getHeight(), 0.1f,
                                                 100.f);
        camera->setPosition(jm::Vec3f(0.0f, 0.0f, 3.0f));
    }

    void update(const float32 deltaTime) override {
        // Update camera position and orientation
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

    void shutDown() override {}

private:
    SharedPtr<Shader> shader = nullptr;
    SharedPtr<VertexBuffer> vbo = nullptr;
    SharedPtr<VertexArray> vao = nullptr;
    SharedPtr<PrespectiveCamera> camera = nullptr;
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp3d(); }

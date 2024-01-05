// C++ system includes
#include <cstdint>

// Jupiter includes
#include <Jupiter.h>

using namespace jupiter;

class DemoJupiterApp2d : public jupiter::Application {
public:
    DemoJupiterApp2d() { init(); }

    ~DemoJupiterApp2d() override { shutDown(); }
    
private:
    void init() override {
        const std::string vertexShaderSource = R"(
        #version 410 core
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec4 color;
        
        uniform mat4 projViewMatrix;
        uniform mat4 modelTransform;
        out vec4 ourColor;
        void main() {
            gl_Position = projViewMatrix * modelTransform * vec4(pos.x, pos.y, pos.z, 1.0);
            ourColor = color;
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

        // Vertex data
        float32 vertices[] = {
            // position         // orange color
            -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,  // left
            0.5f,  -0.5f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,  // right
            0.0f,  0.5f,  0.0f, 1.0f, 0.5f, 0.2f, 1.0f   // top
        };

        // Indices data
        uint32 indices[] = {0, 1, 2};

        // Create shader program, vbo, vao, ebo
        shader = Shader::create(vertexShaderSource, fragmentShaderSource);
        vbo = VertexBuffer::create(vertices, sizeof(vertices));
        ebo = IndexBuffer::create(indices, std::size(indices));
        vao = VertexArray::create();

        // Set vertex buffer layout
        VertexBufferLayoutData posData(ShaderDataType::Float3);
        VertexBufferLayoutData colorData(ShaderDataType::Float4);
        VertexBufferLayout bufferLayout;
        bufferLayout.update(posData);
        bufferLayout.update(colorData);
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
        cameraPos = camera->getPosition();
    }

    void update(const float32 deltaTime) override {
        // Update x- and y-axis coords of the camera position
        float32 velocity = (float32)cameraMoveSpeed * deltaTime;
        if (Input::keyPressed(Keyboard::KEY_A)) {
            cameraPos.x += velocity;
        } else if (Input::keyPressed(Keyboard::KEY_D)) {
            cameraPos.x -= velocity;
        }

        if (Input::keyPressed(Keyboard::KEY_W)) {
            cameraPos.y -= velocity;
        } else if (Input::keyPressed(Keyboard::KEY_S)) {
            cameraPos.y += velocity;
        }

        camera->setPosition(cameraPos);

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
    SharedPtr<IndexBuffer> ebo = nullptr;
    SharedPtr<VertexArray> vao = nullptr;
    SharedPtr<OrthographicCamera> camera = nullptr;
    jm::Vec3f cameraPos;
    float32 cameraMoveSpeed = 1.5f;
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp2d(); }

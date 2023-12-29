// Jpch
#include "Jpch.h"

// Own includes
#include "base/Application.h"
#include "base/Input.h"
#include "events/EventManager.h"
#include "events/KeyboardEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"
#include "ui/imgui/ImGuiUiLayer.h"
#include "renderer/Shader.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"

// Temp includes
#include <glad/glad.h>
#include "renderer/opengl/GLVertexArray.h"

namespace jupiter {

Application* Application::appInstance = nullptr;

Application::Application() {
    appInstance = this;

    // Initialize global memory arena for storing of all input events
    gMemoryArena = newUniquePtr<MemoryArena>(1e6);
    jAssertPtr(gMemoryArena);

    // Initialize global event manager
    gEventManager = newUniquePtr<EventManager>();
    jAssertPtr(gEventManager);

    // Create window
    window = Window::create();
    jAssertPtr(window);

    // Attach UI layer
    uiLayer = newUniquePtr<ImGuiUILayer>();
    uiLayer->attach(UILayerConfig(window.get()));
    jAssertPtr(uiLayer);

    // Window events handlers
    subscribe<WindowCloseEvent>([this](const WindowCloseEvent& event) { onWindowClose(event); });
    subscribe<WindowResizeEvent>([this](const WindowResizeEvent& event) { onEvent(event); });
    // Keyboard events handlers
    subscribe<KeyPressEvent>([this](const KeyPressEvent& event) { onEvent(event); });
    subscribe<KeyReleaseEvent>([this](const KeyReleaseEvent& event) { onEvent(event); });
    // Mouse events handlers
    subscribe<MouseButtonPressEvent>(
        [this](const MouseButtonPressEvent& event) { onEvent(event); });
    subscribe<MouseButtonReleaseEvent>(
        [this](const MouseButtonReleaseEvent& event) { onEvent(event); });
    subscribe<MouseMotionEvent>([this](const MouseMotionEvent& event) { onEvent(event); });
    subscribe<MouseScrollEvent>([this](const MouseScrollEvent& event) { onEvent(event); });
}

Application::~Application() {}

void Application::run() {
    const std::string vertexShaderSource = R"(
        #version 410 core
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec4 color;

        out vec4 ourColor;
        void main() {
            gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
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

    // Create shader object
    SharedPtr<Shader> shader = Shader::create(vertexShaderSource, fragmentShaderSource);
    // Create vertex buffer object
    SharedPtr<VertexBuffer> vbo = VertexBuffer::create(vertices, sizeof(vertices));
    // Create element buffer object
    SharedPtr<IndexBuffer> ebo = IndexBuffer::create(indices, std::size(indices));
    // Create vertex array object
    SharedPtr<VertexArray> vao = VertexArray::create();

    // Set vertex buffer layout
    VertexBufferLayoutData posData(ShaderDataType::Float3);
    VertexBufferLayoutData colorData(ShaderDataType::Float4);

    VertexBufferLayout bufferLayout;
    bufferLayout.update(posData);
    bufferLayout.update(colorData);
    vbo->setBufferLayout(bufferLayout);

    // Add vertex buffer object with set layout to the vao
    // This binds the vao and the vbo
    vao->addVertexBuffer(vbo);
    // Set and bind ebo
    vao->setIndexBuffer(ebo);

    // Unbind the vba and vbo
    vao->unbind();
    vbo->unbind();

    while (running) {
        // Pool events and swap buffers
        window->update();

        // Clear frame
        Renderer::Command::setClearColor(jm::Vec4f(0.45f, 0.55f, 0.60f, 1.00f));
        Renderer::Command::clear();

        // Draw triangle
        shader->bind();
        Renderer::Command::drwaElements(vao);

        // Render UI layer
        uiLayer->update();

        // Dispatch event queue
        dispatchEvents();
    }

    shader->unbind();
    ebo->unbind();
    vao->unbind();
}

void Application::onWindowClose(const WindowCloseEvent& event) {
    running = false;
    JLOG_INFO(event.toString().c_str());
}

void Application::onEvent(const Event& event) {
    JLOG_INFO(event.toString().c_str());
    if (Input::keyPressed(Keyboard::KEY_ESCAPE)) {
        running = false;
    }
}

}  // namespace jupiter

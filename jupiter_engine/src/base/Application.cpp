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

// Temp includes
#include <glad/glad.h>

namespace jupiter {

Application* Application::appInstance = nullptr;

Application::Application() {
    appInstance = this;

    // Initialize global linear allocator for input events
    gLinearAllocator = newUniquePtr<LinearAllocator>(1e6);
    jAssertPtr(gLinearAllocator);

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
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
)";

    const std::string fragmentShaderSource = R"(
        #version 410 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
)";

    // Vertex data
    float32 vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left
        0.5f,  -0.5f, 0.0f,  // right
        0.0f,  0.5f,  0.0f   // top
    };

    // Indices data
    uint32 indices[] = {0, 1, 2};

    // Create shader object
    SharedPtr<Shader> shader = Shader::create(vertexShaderSource, fragmentShaderSource);
    // Create vertex buffer object
    SharedPtr<VertexBuffer> vbo = VertexBuffer::create(vertices, sizeof(vertices));
    // Create element buffer object
    SharedPtr<IndexBuffer> ebo = IndexBuffer::create(indices, std::size(indices));

    // Prepare vertex array object handle
    uint32 VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
    vbo->unbind();

    while (running) {
        window->update();
        uiLayer->update();

        // Draw triangle
        shader->bind();
        ebo->bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, 0);

        // Dispatch event queue
        dispatchEvents();
    }

    shader->unbind();
    ebo->unbind();
    glDeleteVertexArrays(1, &VAO);
}

void Application::onWindowClose(const WindowCloseEvent& event) {
    running = false;
    JLOG_INFO(event.toString().c_str());
}

void Application::onEvent(const Event& event) {
    JLOG_INFO(event.toString().c_str());
    if (Input::isKeyPressed(Keyboard::KEY_ESCAPE)) {
        running = false;
    }
}

}  // namespace jupiter

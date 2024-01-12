// Jpch
#include "Jpch.h"

// Onw includes
#include "ui/imgui/ImGuiUILayer.h"
#include "base/Application.h"
#include "events/EventManager.h"
#include "events/MouseEvents.h"

// Third party includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// Temp includes
#include "math/vector/Vector.h"

namespace jupiter {

ImGuiUILayer::~ImGuiUILayer() {
    if (running)
        detach();
}

void ImGuiUILayer::attach(const UILayerConfig& config) {
    imguiLayerData.theme = config.theme;
    imguiLayerData.nativeWindow = (GLFWwindow*)config.window->getNativeWindow();
    jAssertPtr(imguiLayerData.nativeWindow);
    running = true;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui io
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport/Platform Windows
    io->ConfigDockingWithShift = true;                    // Must hold shift to dock

    // Setup Dear ImGui style
    style = &ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style->WindowRounding = 0.0f;
        style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    setTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(imguiLayerData.nativeWindow, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    JLOG_INFO("ImGui Layer attached and set");
}

void ImGuiUILayer::update(const UIRenderCallback& uiRenderCallback) {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::ShowDemoWindow();

    // Show simple debug information
    {
        GraphicsContext* context = getAppGraphicsContext();
        ImGui::Begin("Debug information");
        ImGui::Text("Graphics API: OpenGL");
        ImGui::Text("Graphics API vendor: %s", context->getVendor());
        ImGui::Text("Graphics API vendor version: %s", context->getVendorVersion());
        ImGui::Text("Graphics API renderer implementation: %s",
                    context->getRendererImplementation());
        ImGui::Text("Used memory: %lld bytes", gMemoryArena->getUsedMemory());
        ImGui::Text("Average frame rate %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate,
                    io->Framerate);
        ImGui::End();
    }

    // Render client ui code here
    { uiRenderCallback(); }

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backUpCurrContex = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backUpCurrContex);
    }
}

void ImGuiUILayer::detach() {
    // Cleanup Dear ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    running = false;
}

void ImGuiUILayer::setTheme() {
    switch (imguiLayerData.theme) {
    case CLASSIC:
        ImGui::StyleColorsClassic();
        break;
    case DARK:
        ImGui::StyleColorsDark();
        break;
    case LIGHT:
        ImGui::StyleColorsLight();
        break;
    default:
        JLOG_ERROR("Unsupported theme provided in ImGuiUILayer::setTheme()");
        jAssertExpr(false);
    }
}

}  // namespace jupiter

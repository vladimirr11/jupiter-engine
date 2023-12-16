// Jpch
#include "Jpch.h"

// Onw includes
#include "ImGuiUILayer.h"

// Third party includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace jupiter {

ImGuiUILayer::~ImGuiUILayer() {}

void ImGuiUILayer::init(const UILayerConfig& config) {
    imguiLayerData.theme = config.theme;
    imguiLayerData.nativeWindow = (GLFWwindow*)config.window->getNativeWindow();
    jAssertPtr(imguiLayerData.nativeWindow);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui io
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable keyboard controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
    // io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable multy-viewport - Windows
    // only
    io->ConfigDockingWithShift = true;  // Must hold shift to dock

    // Setup Dear ImGui style
    style = &ImGui::GetStyle();
    style->WindowRounding = 0.0f;
    style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    setTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(imguiLayerData.nativeWindow, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiUILayer::update() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show simple debug information
    {
        ImGui::Begin("Debug information");
        ImGui::Text("Used memory = %d bytes", gLinearAllocator->getUsedMemory());
        ImGui::Text("Average frame rate %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate,
                    io->Framerate);
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
    ImGui::UpdatePlatformWindows();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiUILayer::shutDown() {
    // Cleanup Dear ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
        JLOG_ERROR("Unsupported action provided in glfwSetKeyCallback function");
        jAssertExpr(false);
    }
}

}  // namespace jupiter

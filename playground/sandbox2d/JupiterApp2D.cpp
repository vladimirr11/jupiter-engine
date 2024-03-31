// C++ system includes
#include <cstdint>

// Jupiter includes
#include <Jupiter.h>
#include <imgui_internal.h>

using namespace jupiter;

class SandboxApp2D : public jupiter::Application {
public:
    SandboxApp2D() { init(); }

    ~SandboxApp2D() override { shutDown(); }

private:
    void init() override {
        // Create an ortho camera with defined viewport and position
        const Window& window = Application::getWindow();
        camera = newSharedPtr<OrthographicCamera>(window.getWidth(), window.getHeight());
        camera->setPosition(jm::Vec3f(.0f, .0f, .0f));

        checkerBoardTex =
            Texture2D::create("playground/sandbox2d/assets/textures/Checkerboard.png");
        dicesTex = Texture2D::create("playground/sandbox2d/assets/textures/Dices.png");

        FramebufferConfig fbConfig;
        fbConfig.width = window.getWidth();
        fbConfig.height = window.getHeight();
        viewportPanelSize.x = window.getWidth();
        viewportPanelSize.y = window.getHeight();
        framebuffer = Framebuffer::create(fbConfig);
    }

    void update(const float32 deltaTime) override {
        // Update camera position in the scene wrt to delta time
        camera->update(deltaTime);

        framebuffer->bind();
        // Clear frame
        Renderer::Command::setClearColor(jm::Vec4f(0.45f, 0.55f, 0.60f, 1.00f));
        Renderer::Command::clear();

        Renderer::beginFrame(camera);

        // Draw quads
        for (float32 y = -5.f; y < 5.f; y += 0.5f) {
            for (float32 x = -5.f; x < 5.f; x += 0.5f) {
                jm::Vec4f quadColor{(x + 0.5f) / 10.f, 0.2f, (y + 0.5f) / 10.f, 0.7f};
                Renderer::Command::drawQuad(
                    QuadDescription{.position{x, y, 0.f}, .size{0.45f, 0.45f}, .color{quadColor}});
            }
        }

        static float32 quadRot = 0.f;
        quadRot += deltaTime * 50.f;
        Renderer::Command::drawQuad(QuadDescription{.position{-0.5f, 0.5f, 0.f},
                                                    .size{1.f, 1.f},
                                                    .color{0.1f, 0.6f, 0.2f, 1.f},
                                                    .texture{checkerBoardTex},
                                                    .texScaler{4},
                                                    .rotation{quadRot}});

        Renderer::Command::drawQuad(
            QuadDescription{.position{0.5f, 0.5f, 0.f}, .size{1.f, 1.f}, .texture{dicesTex}});

        Renderer::Command::drawQuad(QuadDescription{
            .position{-0.8f, 0.f, 0.f}, .size{.5f, .5f}, .color{0.7f, 0.6f, 0.8f, 1.f}});

        Renderer::Command::drawQuad(QuadDescription{
            .position{0.8f, 0.f, 0.f}, .size{.5f, .5f}, .color{0.9f, 0.6f, 0.2f, 1.f}});

        Renderer::finishFrame();
        framebuffer->unbind();
    }

    void uiLayerUpdate() override {
        ImGuiIO& io = ImGui::GetIO();
        const Window& window = Application::getWindow();

        static bool dockSpaceOpen = true;
        static bool fullScreen = true;
        static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;
        if (fullScreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                           ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockSpaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
            windowFlags |= ImGuiWindowFlags_NoBackground;
        }

        // Begin DockSpace
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockSpaceOpen, windowFlags);
        ImGui::PopStyleVar();

        if (fullScreen) {
            ImGui::PopStyleVar(2);
        }

        // Submit the DockSpace
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockSpaceID = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);

            static auto firstTime = true;
            if (firstTime) {
                firstTime = false;
                ImGui::DockBuilderRemoveNode(dockSpaceID);
                ImGui::DockBuilderAddNode(dockSpaceID,
                                          dockSpaceFlags | ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockSpaceID, ImGui::GetWindowSize());
                ImGuiID dockspaceMainNodeID = dockSpaceID;
                ImGuiID leftNodeID = ImGui::DockBuilderSplitNode(
                    dockspaceMainNodeID, ImGuiDir_Left, 0.3f, nullptr, &dockspaceMainNodeID);

                ImGui::DockBuilderDockWindow("Debug information", leftNodeID);
                ImGui::DockBuilderDockWindow("Viewport", dockspaceMainNodeID);
                ImGui::DockBuilderFinish(dockSpaceID);
            }
        }

        // Begin Debug information panel
        {
            GraphicsContext* context = getAppGraphicsContext();

            ImGui::Begin("Debug information");
            ImGui::Text("Graphics API: OpenGL");
            ImGui::Text("Graphics API vendor: %s", context->getVendor());
            ImGui::Text("Graphics API vendor version: %s", context->getVendorVersion());
            ImGui::Text("Graphics API renderer implementation: %s",
                        context->getRendererImplementation());
            ImGui::Text("Consumed events memory: %lld bytes", getMemoryArenaUsedMemory());
            ImGui::Text("Average frame rate %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                        io.Framerate);
            ImGui::Text("Batch Renderer stats: #draw calls %d",
                        Renderer::Statistics::getDrawCalls());
            ImGui::Text("Batch Renderer stats: #draw quads %d",
                        Renderer::Statistics::getDrawQuads());
            ImGui::Text("Batch Renderer stats: #draw verts %d",
                        Renderer::Statistics::getDrawVertices());
            ImGui::End();
        }

        // Begin Viewport panel
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Viewport");
            ImGui::PopStyleVar();

            ImVec2 viewportDims = ImGui::GetContentRegionAvail();
            // JLOG_WARN("Viewport dims [{}, {}]", viewportDims.x, viewportDims.y);
            if (viewportPanelSize.x != viewportDims.x || viewportPanelSize.y != viewportDims.y) {
                framebuffer->resize(viewportDims.x, viewportDims.y);
                viewportPanelSize = {viewportDims.x, viewportDims.y};
                camera->setViewport(viewportDims.x, viewportDims.y);
            }
            const uint32 viewportTextureId = framebuffer->getColorAttachmentId();
            ImGui::Image((void*)viewportTextureId, ImVec2{viewportPanelSize.x, viewportPanelSize.y},
                         ImVec2{0, 1}, ImVec2{1, 0});
            ImGui::End();
        }

        // End dock space
        ImGui::End();
    }

    void shutDown() override {}

private:
    SharedPtr<OrthographicCamera> camera = nullptr;
    SharedPtr<Framebuffer> framebuffer = nullptr;
    jm::Vec2f viewportPanelSize = jm::Vec2f();
    SharedPtr<Texture2D> checkerBoardTex = nullptr;
    SharedPtr<Texture2D> dicesTex = nullptr;
};

jupiter::Application* jupiter::createApplication() { return new SandboxApp2D(); }

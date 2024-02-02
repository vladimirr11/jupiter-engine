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
        // Create an ortho camera with defined viewport and position
        const Window& window = Application::getWindow();
        camera = newSharedPtr<OrthographicCamera>(window.getWidth(), window.getHeight());
        camera->setPosition(jm::Vec3f(.0f, .0f, .0f));

        checkerBoardTex = Texture2D::create("2dsandbox/assets/textures/Checkerboard.png");
        dicesTex = Texture2D::create("2dsandbox/assets/textures/Dices.png");
    }

    void update(const float32 deltaTime) override {
        // Update camera position in the scene wrt to delta time
        camera->update(deltaTime);

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
    }

    void uiLayerUpdate() override {
        ImGuiIO* io = &ImGui::GetIO();
        GraphicsContext* context = getAppGraphicsContext();
        ImGui::Begin("Debug information");
        ImGui::Text("Graphics API: OpenGL");
        ImGui::Text("Graphics API vendor: %s", context->getVendor());
        ImGui::Text("Graphics API vendor version: %s", context->getVendorVersion());
        ImGui::Text("Graphics API renderer implementation: %s",
                    context->getRendererImplementation());
        ImGui::Text("Consumed events memory: %lld bytes", getMemoryArenaUsedMemory());
        ImGui::Text("Average frame rate %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate,
                    io->Framerate);
        ImGui::Text("Batch Renderer stats: #draw calls %d", Renderer::Statistics::getDrawCalls());
        ImGui::Text("Batch Renderer stats: #draw quads %d", Renderer::Statistics::getDrawQuads());
        ImGui::Text("Batch Renderer stats: #draw verts %d",
                    Renderer::Statistics::getDrawVertices());
        ImGui::End();
    }

    void shutDown() override {}

private:
    SharedPtr<OrthographicCamera> camera = nullptr;
    SharedPtr<Texture2D> checkerBoardTex = nullptr;
    SharedPtr<Texture2D> dicesTex = nullptr;
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp2d(); }

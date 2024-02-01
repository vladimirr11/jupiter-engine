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

        Renderer::Command::drawQuad(QuadDescription{.position{-0.5f, 0.5f, 0.f},
                                                    .size{1.f, 1.f},
                                                    .color{0.1f, 0.6f, 0.2f, 1.f},
                                                    .texture{checkerBoardTex},
                                                    .texScaler{4},
                                                    .rotation{15.f}});

        Renderer::Command::drawQuad(
            QuadDescription{.position{0.5f, 0.5f, 0.f}, .size{1.f, 1.f}, .texture{dicesTex}});

        Renderer::Command::drawQuad(QuadDescription{
            .position{-0.8f, 0.f, 0.f}, .size{.5f, .5f}, .color{0.7f, 0.6f, 0.8f, 1.f}});

        Renderer::Command::drawQuad(QuadDescription{
            .position{0.8f, 0.f, 0.f}, .size{.5f, .5f}, .color{0.9f, 0.6f, 0.2f, 1.f}});

        Renderer::finishFrame();
    }

    void uiLayerUpdate() override {}

    void shutDown() override {}

private:
    SharedPtr<OrthographicCamera> camera = nullptr;
    SharedPtr<Texture2D> checkerBoardTex = nullptr;
    SharedPtr<Texture2D> dicesTex = nullptr;
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp2d(); }

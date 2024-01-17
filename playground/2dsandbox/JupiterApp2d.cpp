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
    }

    void update(const float32 deltaTime) override {
        // Update camera position in the scene wrt to delta time
        camera->update(deltaTime);

        // Clear frame
        Renderer::Command::setClearColor(jm::Vec4f(0.45f, 0.55f, 0.60f, 1.00f));
        Renderer::Command::clear();

        // Set scene camera
        Renderer::beginFrame(camera);

        // Draw quad
        Renderer::Command::drawQuad(Quad({0.0f, 0.f, 0.f}, {3.f, 3.0f, 0.f}, {}, {}, 1u));

        // Doesn't do anything for now
        Renderer::finishFrame();
    }

    void uiLayerUpdate() override {
        // Set tringle color
        // ImGui::Begin("Color Settings");
        // ImGui::ColorEdit3("Triangle Color", &triangleColor[0]);
        // ImGui::End();

        //// Send color to the device
        // shader->bind();
        // shader->setUniformVec3f("myColor", triangleColor);
        // shader->unbind();
    }

    void shutDown() override {}

private:
    SharedPtr<OrthographicCamera> camera = nullptr;
};

jupiter::Application* jupiter::createApplication() { return new DemoJupiterApp2d(); }

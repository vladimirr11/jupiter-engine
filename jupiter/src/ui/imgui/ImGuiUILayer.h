#pragma once

// Own includes
#include "ui/UILayer.h"

struct GLFWwindow;
struct ImGuiStyle;
struct ImGuiIO;

namespace jupiter {

class ImGuiUILayer : public UILayer {
public:
    ImGuiUILayer() = default;

    ~ImGuiUILayer();

    void attach(const UILayerConfig& config) override;
    void detach() override;

    void update() override;

private:
    void setTheme();

    struct ImGuiUILayerData {
        UITheme theme = UITheme::CLASSIC;
        GLFWwindow* nativeWindow = nullptr;
    };

private:
    ImGuiUILayerData imguiLayerData;
    ImGuiStyle* style = nullptr;
    ImGuiIO* io = nullptr;
    bool running = false;
};

}  // namespace jupiter

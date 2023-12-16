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

    void init(const UILayerConfig& config) override;
    void shutDown() override;

    void update() override;

private:
    void setTheme();

    struct ImGuiUILayerData {
        UITheme theme;
        GLFWwindow* nativeWindow = nullptr;
    };

private:
    ImGuiUILayerData imguiLayerData;
    ImGuiStyle* style = nullptr;
    ImGuiIO* io = nullptr;
};

}  // namespace jupiter

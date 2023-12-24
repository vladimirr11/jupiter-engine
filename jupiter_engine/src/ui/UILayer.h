#pragma once

#include "base/Window.h"

namespace jupiter {

enum UITheme { CLASSIC, DARK, LIGHT };

struct UILayerConfig {
    Window* window = nullptr;
    UITheme theme;

    UILayerConfig(Window* window_, const UITheme theme_ = DARK) : window(window_), theme(theme_) {}
};

class UILayer {
public:
    virtual ~UILayer() = default;

    virtual void attach(const UILayerConfig& config) = 0;
    virtual void detach() = 0;

    virtual void update() = 0;
};

}  // namespace jupiter
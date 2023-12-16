#pragma once

#include "base/Window.h"

namespace jupiter {

enum UITheme { CLASSIC, DARK, LIGHT };

struct UILayerConfig {
    UITheme theme;
    Window* window = nullptr;

    UILayerConfig(Window* window_, const UITheme theme_ = DARK) : window(window_), theme(theme_) {}
};

class UILayer {
public:
    virtual ~UILayer() = default;

    virtual void init(const UILayerConfig& config) = 0;
    virtual void shutDown() = 0;

    virtual void update() = 0;
};

}  // namespace jupiter
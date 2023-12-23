#pragma once

namespace jupiter {

class GraphicsContext {
public:
    ~GraphicsContext() = default;

    virtual void init() = 0;
    virtual void swapBuffers() const = 0;
};

}  // namespace jupiter
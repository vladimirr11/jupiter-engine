#pragma once

// Own includes
#include "renderer/VertexArray.h"
#include "math/vector/Vector.h"

namespace jupiter {

class RendererBackend {
public:
    enum GraphicsAPI { None, OpenGL };

public:
    virtual ~RendererBackend() = default;

    virtual void init() const = 0;
    virtual void shutDown() const = 0;

    virtual void clear() const = 0;
    virtual void setClearColor(const jm::Vec4f& color) const = 0;
    virtual void setViewport(const float32 width, const float32 height) const = 0;

    virtual void drawElements(const SharedPtr<VertexArray>& vertArray) const = 0;

    static GraphicsAPI getGraphicsAPI() { return graphicsApi; }

    static UniquePtr<RendererBackend> create();

private:
#ifdef GRAPHICS_API_OPENGL
    inline static GraphicsAPI graphicsApi = GraphicsAPI::OpenGL;
#else
    inline static GraphicsAPI graphicsApi = GraphicsAPI::None;
#endif  // GRAPHICS_API_OPENGL
};

}  // namespace jupiter

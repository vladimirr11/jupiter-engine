#pragma once

// Onw includes
#include "renderer/RendererBackend.h"

namespace jupiter {

class GLRenderer : public RendererBackend {
public:
    ~GLRenderer() override;

    void init() const override;
    void shutDown() const override;

    void clear() const override;
    void setClearColor(const jm::Vec4f& color) const override;
    void setViewport(const uint32 width, const uint32 height) const override;

    void drawElements(const SharedPtr<VertexArray>& vertArray) const override;
};

}  // namespace jupiter

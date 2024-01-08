#pragma once

// Own includes
#include "renderer/Texture.h"

namespace jupiter {

class GLTexture : public Texture2D {
public:
    GLTexture(const FilesysPath& path);

    ~GLTexture() override;

    void bind(const uint32 slot = 0) const override;

    int32 getWidth() const override { return texData.width; }
    int32 getHeight() const override { return texData.height; }
    ColorFormat getFormat() const override { return texData.format; }

private:
    TextureData texData;
    uint32 textureId;
};

}  // namespace jupiter

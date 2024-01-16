#pragma once

// Own includes
#include "renderer/Texture.h"

namespace jupiter {

class GLTexture : public Texture2D {
public:
    GLTexture(const FilesysPath& path);

    ~GLTexture() override;

    void bind(const uint32 slot = 0) const override;
    void unbind() const override;

    int32 getWidth() const override { return texPayload.width; }
    int32 getHeight() const override { return texPayload.height; }
    ColorFormat getFormat() const override { return texPayload.format; }

private:
    TexturePayload texPayload;
    uint32 textureId;
};

}  // namespace jupiter

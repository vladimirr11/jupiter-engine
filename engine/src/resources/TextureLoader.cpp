// Jpch
#include "Jpch.h"

// Own includes
#include "resources/TextureLoader.h"
#include "base/Assert.h"

// Third-party includes
#include <stb_image.h>

namespace jupiter {

TexturePayload TextureLoader::loadFromFile(const FilesysPath& texturePath) {
    TexturePayload texPayload;
    stbi_set_flip_vertically_on_load(true); // Flip loaded texture on the y-axis
    texPayload.buffer = stbi_load(texturePath.string().c_str(), &texPayload.width,
                                  &texPayload.height, &texPayload.numChannels, 0);
    jAssertPtr(texPayload.buffer);
    jAssertExpr(texPayload.width != 0);
    jAssertExpr(texPayload.height != 0);

    switch (texPayload.numChannels) {
    case 4:
        texPayload.format = ColorFormat::RGBA;
        break;
    case 3:
        texPayload.format = ColorFormat::RGB;
        break;
    default:
        JLOG_ERROR("Unsupported number of channels returned by stbi_load");
        break;
    }
    texPayload.hasBuffer = true;

    JLOG_INFO("Texture loaded from path {}", texturePath.string());
    return texPayload;
}

}  // namespace jupiter

// Jpch
#include "Jpch.h"

// Own includes
#include "resources/TextureLoader.h"
#include "base/Assert.h"

// Third-party includes
#include <stb_image.h>

namespace jupiter {

TextureData TextureLoader::loadFromFile(const FilesysPath& texturePath) {
    std::cout << texturePath << std::endl;
    TextureData texData;
    texData.buffer =
        stbi_load("C:/Users/user/source/jupiter_engine/playground/2dsandbox/assets/DemoTexture.png",
                  &texData.width, &texData.height, &texData.numChannels, 0);
    jAssertPtr(texData.buffer);
    jAssertExpr(texData.width != 0);
    jAssertExpr(texData.height != 0);

    switch (texData.numChannels) {
    case 4:
        texData.format = ColorFormat::RGBA;
        break;
    case 3:
        texData.format = ColorFormat::RGB;
        break;
    default:
        JLOG_ERROR("Unsupported number of channels returned by stbi_load");
        break;
    }
    texData.hasBuffer = true;

    JLOG_INFO("Texture loaded from path {}", (const int8*)texturePath.c_str());
    return texData;
}

}  // namespace jupiter

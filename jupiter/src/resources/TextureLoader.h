#pragma once

// C++ system includes
#include <filesystem>

// Own includes
#include "base/Defines.h"

namespace jupiter {

enum class ColorFormat { None, RGB, RGBA };

struct TexturePayload {
    uint8* buffer = nullptr;
    int32 width = 0;
    int32 height = 0;
    int32 numChannels = 0;
    ColorFormat format = ColorFormat::None;
    bool hasBuffer = false;
};

class TextureLoader {
public:
    static TexturePayload loadFromFile(const FilesysPath& texturePath);
};

}  // namespace jupiter

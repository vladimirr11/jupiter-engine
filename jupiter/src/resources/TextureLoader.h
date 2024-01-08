#pragma once

// C++ system includes
#include <filesystem>

// Own includes
#include "base/Defines.h"

namespace jupiter {

enum class ColorFormat { None, RGB, RGBA };

using FilesysPath = std::filesystem::path;

struct TextureData {
    uint8* buffer = nullptr;
    int32 width = 0;
    int32 height = 0;
    int32 numChannels = 0;
    ColorFormat format = ColorFormat::None;
    bool hasBuffer = false;
};

class TextureLoader {
public:
    static TextureData loadFromFile(const FilesysPath& texturePath);
};

}  // namespace jupiter

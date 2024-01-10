#pragma once

// C++ system includes
#include <string>

// Own inludes
#include "base/Defines.h"

namespace jupiter {

class ShaderLoader {
public:
    static std::string loadVertexShader(const FilesysPath& vsPath);
    static std::string loadFragmentShader(const FilesysPath& fsPath);

private:
    static std::string readShader(const FilesysPath& path);
};

}  // namespace jupiter
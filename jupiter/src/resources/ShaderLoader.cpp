// Jpch
#include "Jpch.h"

// Own includes
#include "resources/ShaderLoader.h"
#include "base/Assert.h"

namespace jupiter {

std::string ShaderLoader::loadVertexShader(const FilesysPath& vsPath) {
    if (vsPath.extension() != ".vert") {
        JLOG_ERROR("Note: Jupiter vertex shader file extension is .vert, instead {} was provided",
                   vsPath.extension().generic_string());
        jAssertExpr(false);
    }
    return readShader(vsPath);
}

std::string ShaderLoader::loadFragmentShader(const FilesysPath& fsPath) {
    if (fsPath.extension() != ".frag") {
        JLOG_ERROR("Note: Jupiter fragment shader file extension is .frag, instead {} was provided",
                   fsPath.extension().generic_string());
        jAssertExpr(false);
    }
    return readShader(fsPath);
}

std::string ShaderLoader::readShader(const FilesysPath& path) {
    std::ifstream inStream(path.generic_string(), std::ios::in | std::ios::binary);
    if (!inStream.good()) {
        JLOG_ERROR("Error bit was raised during reading of file {}", path.generic_string());
        jAssertExpr(false);
    }
    inStream.seekg(0, std::ios::end);
    const auto fileSize = inStream.tellg();
    std::string shaderSource(fileSize, 0);
    inStream.seekg(std::ios::beg);
    inStream.read(&shaderSource[0], fileSize);
    inStream.close();

    return shaderSource;
}

}  // namespace jupiter

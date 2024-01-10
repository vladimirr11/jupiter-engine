// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/Shader.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLShader.h"
#endif

namespace jupiter {

SharedPtr<Shader> Shader::create(const std::string& vsSource, const std::string& fsSource) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLShader>(vsSource, fsSource);
#endif  // GRAPHICS_API_OPENGL
}

SharedPtr<Shader> Shader::create(const FilesysPath& vsPath, const FilesysPath& fsPath) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLShader>(vsPath, fsPath);
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

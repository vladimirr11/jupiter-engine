// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/Shader.h"
#include "base/BaseDefines.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLShader.h"
#endif

namespace jupiter {

SharedPtr<Shader> Shader::create(const std::string& vsSource, const std::string& fsSource) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLShader>(vsSource, fsSource);
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

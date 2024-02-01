// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/Texture.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLTexture.h"
#endif  // GRAPHICS_API_OPENGL

namespace jupiter {

SharedPtr<Texture2D> Texture2D::create(const FilesysPath& path) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLTexture>(path);
#endif  // GRAPHICS_API_OPENGL
}

SharedPtr<Texture2D> Texture2D::createWhite() {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLTexture>();
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

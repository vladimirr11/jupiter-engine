// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/RendererBackend.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLREnderer.h"
#endif  // GRAPHICS_API_OPENGL

namespace jupiter {

UniquePtr<RendererBackend> RendererBackend::create() {
#ifdef GRAPHICS_API_OPENGL
    return newUniquePtr<GLRenderer>();
#endif  // GRAPHICS_API_OPENGL
    
}

}  // namespace jupiter

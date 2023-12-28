// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/VertexArray.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLVertexArray.h"
#endif

namespace jupiter {

SharedPtr<VertexArray> VertexArray::create() {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLVertexArray>();
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

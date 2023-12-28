// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/VertexBuffer.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLVertexBuffer.h"
#endif

namespace jupiter {

SharedPtr<VertexBuffer> VertexBuffer::create(const void* data, const uint32 numBytes) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLVertexBuffer>(data, numBytes);
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

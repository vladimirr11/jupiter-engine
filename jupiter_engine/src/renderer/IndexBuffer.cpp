// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/IndexBuffer.h"
#ifdef GRAPHICS_API_OPENGL
#include "renderer/opengl/GLIndexBuffer.h"
#endif

namespace jupiter {

SharedPtr<IndexBuffer> IndexBuffer::create(const uint32* data, const uint32 numIndices) {
#ifdef GRAPHICS_API_OPENGL
    return newSharedPtr<GLIndexBuffer>(data, numIndices);
#endif  // GRAPHICS_API_OPENGL
}

}  // namespace jupiter

#pragma once

// Own includes
#include "base/Assert.h"

// Third-party includes
#include <glad/glad.h>

namespace jupiter {

#ifdef DEBUG
#define GLCALL(glfunc)                                                                          \
    (glfunc);                                                                                   \
    {                                                                                           \
        GLenum err;                                                                             \
        while ((err = glGetError()) != GL_NO_ERROR) {                                           \
            JLOG_ERROR("{} function returned error code {} at {} line {}", #glfunc, (int32)err, \
                       __FILE__, __LINE__);                                                     \
        }                                                                                       \
    }
#else
#define GLCALL(glfunc) (func)
#endif  // DEBUG

}  // namespace jupiter

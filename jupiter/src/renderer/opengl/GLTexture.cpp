// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLTexture.h"
#include "base/Assert.h"

// Third-party includes
#include <glad/glad.h>
#include <stb_image.h>

namespace jupiter {

GLTexture::GLTexture(const FilesysPath& path) {
    // Load texture data
    texData = TextureLoader::loadFromFile(path);
    // Prepare texture handle
    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);

    auto colorFormat2OpenGLColorFormat = [](const ColorFormat format) {
        GLenum internalFormat;
        switch (format) {
        case ColorFormat::RGB:
            internalFormat = GL_RGB;
            break;
        case ColorFormat::RGBA:
            internalFormat = GL_RGBA;
            break;
        default:
            JLOG_ERROR("Unsupported color format provided in colorFormat2OpenGLColorFormat: {}",
                       (uint32)format);
            jAssertExpr(false);
        }
        return internalFormat;
    };

    glTextureStorage2D(textureId, 1, colorFormat2OpenGLColorFormat(texData.format), texData.width,
                       texData.height);

    // Set texture wrapping to GL_REPEAT (default wrapping method)
    glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free texture image
    stbi_image_free(texData.buffer);
    texData.hasBuffer = false;
}

GLTexture::~GLTexture() { glDeleteTextures(1, &textureId); }

void GLTexture::bind(const uint32 slot) const { glBindTextureUnit(slot, textureId); }

}  // namespace jupiter

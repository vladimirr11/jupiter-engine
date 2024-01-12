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
    texPayload = TextureLoader::loadFromFile(path);

    // Prepare texture handle
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    auto colorFormat2OpenGLColorFormat = [](const ColorFormat format) {
        GLenum internalFormat;
        GLenum dataFormat;
        switch (format) {
        case ColorFormat::RGB:
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
            break;
        case ColorFormat::RGBA:
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
            break;
        default:
            JLOG_ERROR("Unsupported color format provided in colorFormat2OpenGLColorFormat: {}",
                       (uint32)format);
            jAssertExpr(false);
        }
        return std::make_pair(internalFormat, dataFormat);
    };

    const auto [baseInternalFormat, dataFormat] = colorFormat2OpenGLColorFormat(texPayload.format);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, baseInternalFormat, texPayload.width, texPayload.height, 0,
                 dataFormat, GL_UNSIGNED_BYTE, texPayload.buffer);

    glGenerateMipmap(GL_TEXTURE_2D);

    // Set texture mag/min filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set texture wrapping to GL_REPEAT (default)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Free texture image
    stbi_image_free(texPayload.buffer);
    texPayload.hasBuffer = false;
}

GLTexture::~GLTexture() { glDeleteTextures(1, &textureId); }

void GLTexture::bind(const uint32 slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // glBindTextureUnit(slot, textureId);
}

}  // namespace jupiter

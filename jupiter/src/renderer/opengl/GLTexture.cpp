// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLTexture.h"
#include "renderer/opengl/GLAssert.h"

// Third-party includes
#include <stb_image.h>

namespace jupiter {

GLTexture::GLTexture() {
    // Prepare texture handle
    GLCALL(glGenTextures(1, &textureId));
    GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));

    // Set texture mag/min filtering parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // Set texture wrapping
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    uint32 whiteCol = 0xffffffff;
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whiteCol));

    // Unbind texture
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

GLTexture::GLTexture(const FilesysPath& path) {
    // Load texture data
    texPayload = TextureLoader::loadFromFile(path);

    // Prepare texture handle
    GLCALL(glGenTextures(1, &textureId));
    GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));

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

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, baseInternalFormat, texPayload.width, texPayload.height,
                        0, dataFormat, GL_UNSIGNED_BYTE, texPayload.buffer));

    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

    // Set texture mag/min filtering parameters
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // Set texture wrapping to GL_REPEAT (default)
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    // Unbind texture
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    // Free texture image
    stbi_image_free(texPayload.buffer);
    texPayload.hasBuffer = false;
}

GLTexture::~GLTexture() { glDeleteTextures(1, &textureId); }

void GLTexture::bind(const uint32 slot) const {
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));
}

void GLTexture::unbind() const { GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); }

}  // namespace jupiter

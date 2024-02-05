// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLShader.h"
#include "base/Assert.h"
#include "resources/ShaderLoader.h"
#include "renderer/opengl/GLAssert.h"

namespace jupiter {

GLShader::GLShader(const FilesysPath& vsPath, const FilesysPath& fsPath) {
    const std::string vsSource = ShaderLoader::loadVertexShader(vsPath);
    const std::string fsSource = ShaderLoader::loadFragmentShader(fsPath);
    compileAndLink(vsSource, fsSource);
}

GLShader::~GLShader() { glDeleteProgram(programId); }

void GLShader::bind() const { GLCALL(glUseProgram(programId)); }

void GLShader::unbind() const { GLCALL(glUseProgram(0)); }

void GLShader::setUniformInt(std::string_view name, const int32 uniformId) const {
    int32 loc = glGetUniformLocation(programId, name.data());
    GLCALL(glUniform1i(loc, uniformId));
}

void GLShader::setUniformIntArray(std::string_view name, const int32* array,
                                  const int32 size) const {
    int32 loc = glGetUniformLocation(programId, name.data());
    GLCALL(glUniform1iv(loc, size, array));
}

void GLShader::setUniformVec3f(std::string_view name, const jm::Vec3f& vec3) const {
    int32 loc = glGetUniformLocation(programId, name.data());
    GLCALL(glUniform3fv(loc, 1, &vec3[0]));
}

void GLShader::setUniformVec4f(std::string_view name, const jm::Vec4f& vec4) const {
    int32 loc = glGetUniformLocation(programId, name.data());
    GLCALL(glUniform4fv(loc, 1, &vec4[0]));
}

void GLShader::setUniformMat4x4f(std::string_view name, const jm::Matrix4x4& mat4) const {
    int32 loc = glGetUniformLocation(programId, name.data());
    GLCALL(glUniformMatrix4fv(loc, 1, GL_FALSE, &mat4[0][0]));
}

void GLShader::compileShader(const std::string& shaderSource, const uint32 shaderId) const {
    // Send the shader source code to GL
    const int8* source = shaderSource.c_str();
    GLCALL(glShaderSource(shaderId, 1, &source, 0));

    // Compile the shader
    GLCALL(glCompileShader(shaderId));

    // Assert that the shader compiled
    int32 isCompiled = 0;
    GLCALL(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled));
    if (!isCompiled) {
        // Get log message for the compilation process
        const int32 maxLogLength = 1024;
        int8 logMessage[maxLogLength]{};
        GLCALL(glGetShaderInfoLog(shaderId, maxLogLength, nullptr, &logMessage[0]));

        // We don't need that shader
        GLCALL(glDeleteShader(shaderId));

        // Log the error and exit
        JLOG_ERROR(logMessage);
        exit(EXIT_FAILURE);
    }
}

void GLShader::linkProgram() const {
    // Link our program
    GLCALL(glLinkProgram(programId));

    // Assert linking succeded
    int32 isLinked = 0;
    GLCALL(glGetProgramiv(programId, GL_LINK_STATUS, &isLinked));
    if (isLinked == GL_FALSE) {
        // Get log message for the linking process
        const int32 maxLogLength = 1024;
        int8 logMessage[maxLogLength]{};
        GLCALL(glGetProgramInfoLog(programId, maxLogLength, nullptr, &logMessage[0]));

        // We don't need that program anymore
        GLCALL(glDeleteProgram(programId));

        // Log the error and exit
        JLOG_ERROR(logMessage);
        exit(EXIT_FAILURE);
    }
}

void GLShader::compileAndLink(const std::string& vsSource, const std::string& fsSource) {
    // Compile the vertex shader
    uint32 vertShaderId = GLCALL(glCreateShader(GL_VERTEX_SHADER));
    compileShader(vsSource, vertShaderId);

    // Compile the fragment shader
    uint32 fragShaderId = GLCALL(glCreateShader(GL_FRAGMENT_SHADER));
    compileShader(fsSource, fragShaderId);

    // Get the program object id
    programId = glCreateProgram();

    // Attach our shaders to our program
    GLCALL(glAttachShader(programId, vertShaderId));
    GLCALL(glAttachShader(programId, fragShaderId));

    // Link our program
    linkProgram();

    // Detach shaders after a successful link
    GLCALL(glDetachShader(programId, vertShaderId));
    GLCALL(glDetachShader(programId, fragShaderId));
}

}  // namespace jupiter

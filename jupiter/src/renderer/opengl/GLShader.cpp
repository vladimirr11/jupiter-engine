// Jpch
#include "Jpch.h"

// Own includes
#include "renderer/opengl/GLShader.h"
#include "base/Assert.h"

// Third party includes
#include <glad/glad.h>

namespace jupiter {

GLShader::GLShader(const std::string& vsSource, const std::string& fsSource) {
    // Compile the vertex shader
    uint32 vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vsSource, vertShaderId);

    // Compile the fragment shader
    uint32 fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fsSource, fragShaderId);

    // Get the program object id
    programId = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(programId, vertShaderId);
    glAttachShader(programId, fragShaderId);

    // Link our program
    linkProgram();

    // Detach shaders after a successful link
    glDetachShader(programId, vertShaderId);
    glDetachShader(programId, fragShaderId);
}

void GLShader::compileShader(const std::string& shaderSource, const uint32 shaderId) const {
    // Send the shader source code to GL
    const int8* source = shaderSource.c_str();
    glShaderSource(shaderId, 1, &source, 0);

    // Compile the shader
    glCompileShader(shaderId);

    // Assert that the shader compiled
    int32 isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
        // Get log message for the compilation process
        const int32 maxLogLength = 1024;
        int8 logMessage[maxLogLength]{};
        glGetShaderInfoLog(shaderId, maxLogLength, nullptr, &logMessage[0]);

        // We don't need that shader
        glDeleteShader(shaderId);

        // Log the error and exit
        JLOG_ERROR(logMessage);
        exit(EXIT_FAILURE);
    }
}

void GLShader::linkProgram() const {
    // Link our program
    glLinkProgram(programId);

    // Assert linking succeded
    int32 isLinked = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        // Get log message for the linking process
        const int32 maxLogLength = 1024;
        int8 logMessage[maxLogLength]{};
        glGetProgramInfoLog(programId, maxLogLength, nullptr, &logMessage[0]);

        // We don't need that program anymore
        glDeleteProgram(programId);

        // Log the error and exit
        JLOG_ERROR(logMessage);
        exit(EXIT_FAILURE);
    }
}

GLShader::~GLShader() { glDeleteProgram(programId); }

void GLShader::bind() const { glUseProgram(programId); }

void GLShader::unbind() const { glUseProgram(0); }

}  // namespace jupiter

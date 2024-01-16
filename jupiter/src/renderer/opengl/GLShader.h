#pragma once

// C++ system includes
#include <string>

// Own includes
#include "renderer/Shader.h"
#include "base/Defines.h"

namespace jupiter {

class GLShader : public Shader {
public:
    // Ctor
    GLShader(const FilesysPath& vsPath, const FilesysPath& fsPath);

    // Dtor
    ~GLShader() override;

    void bind() const override;
    void unbind() const override;

    // Uniform setters
    void setUniformInt(std::string_view name, const int32 uniformId) const override;
    void setUniformVec3f(std::string_view name, const jm::Vec3f& vec3) const override;
    void setUniformVec4f(std::string_view name, const jm::Vec4f& vec4) const override;
    void setUniformMat4x4f(std::string_view name, const jm::Matrix4x4& mat4) const override;

private:
    void compileShader(const std::string& shaderSource, const uint32 shaderId) const;
    void linkProgram() const;
    void compileAndLink(const std::string& vsSource, const std::string& fsSource);

private:
    uint32 programId = 0u;
};

}  // namespace jupiter

#pragma once

// C++ system includes
#include <string>

// Own includes
#include "base/Defines.h"
#include "math/matrix/Matrix4x4.h"

namespace jupiter {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setUniformInt(std::string_view name, const int32 uniformId) const = 0;
    virtual void setUniformVec3f(std::string_view name, const jm::Vec3f& vec3) const = 0;
    virtual void setUniformVec4f(std::string_view name, const jm::Vec4f& vec4) const = 0;
    virtual void setUniformMat4x4f(std::string_view name, const jm::Matrix4x4& mat4) const = 0;

    static SharedPtr<Shader> create(const std::string& vsSource, const std::string& fsSource);
    static SharedPtr<Shader> create(const FilesysPath& vsPath, const FilesysPath& fsPath);
};

}  // namespace jupiter

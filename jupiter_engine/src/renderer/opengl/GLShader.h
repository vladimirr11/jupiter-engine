#pragma once

// C++ system includes
#include <string>

// Own includes
#include "renderer/Shader.h"
#include "base/BaseDefines.h"

namespace jupiter {

class GLShader : public Shader {
public:
    GLShader(const std::string& vsSource, const std::string& fsSource);

    ~GLShader() override;

    void bind() const override;
    void unbind() const override;

private:
    void compileShader(const std::string& shaderSource, const uint32 shaderId) const;
    void linkProgram() const;

private:
    uint32 programId;
};

}  // namespace jupiter

#pragma once

// C++ system includes
#include <string>

// Own includes
#include "base/BaseDefines.h"

namespace jupiter {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static SharedPtr<Shader> create(const std::string& vsSource, const std::string& fsSource);
};

}  // namespace jupiter

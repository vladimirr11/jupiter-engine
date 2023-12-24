#pragma once

namespace jupiter {

class Shader {
public:
    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};

}  // namespace jupiter
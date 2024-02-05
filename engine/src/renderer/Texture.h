#pragma once

// Own includes
#include "resources/TextureLoader.h"

namespace jupiter {

class Texture {
public:
    virtual ~Texture() = default;

    virtual void bind(const uint32 slot = 0) const = 0;
    virtual void unbind() const = 0;

    virtual int32 getWidth() const = 0;
    virtual int32 getHeight() const = 0;
    virtual int32 getId() const = 0;
    virtual ColorFormat getFormat() const = 0;
};

class Texture2D : public Texture {
public:
    static SharedPtr<Texture2D> create(const FilesysPath& path);
    static SharedPtr<Texture2D> createWhite();
};

}  // namespace jupiter

#pragma once

// C++ system includes
#include <vector>
#include <array>

// Own includes
#include "renderer/VertexBuffer.h"
#include "base/Assert.h"

namespace jupiter {

enum ShaderDataType { None, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Bool };

class VertexBufferLayoutData {
public:
    VertexBufferLayoutData() = default;

    VertexBufferLayoutData(const ShaderDataType type_, bool normalized_ = false)
        : type(type_), normalized(normalized_) {
        // Look up tables used to extract the respective count and stride by given shader data type
        static const std::array shaderDataTypeLookUpCounts{0u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u};
        static const std::array shaderDataTypeLookUpStrides{0u, 4u, 8u,  12u, 16u,
                                                            4u, 8u, 12u, 16u, 1u};
        count = shaderDataTypeLookUpCounts[type];
        stride = shaderDataTypeLookUpStrides[type];
    }

    inline uint32 getCount() const { return count; }

    inline ShaderDataType getType() const {
        jAssertExpr(type != ShaderDataType::None);
        return type;
    }

    inline bool isNormalized() const { return normalized; }

    inline uint32 getStride() const { return stride; }

    inline const void* getOffset() const { return (const void*)offset; }
    inline void setOffset(const uint32 newOffset) { offset = newOffset; }

private:
    uint32 count = 0;
    ShaderDataType type = ShaderDataType::None;
    bool normalized = false;
    uint32 stride = 0;
    uint32 offset = 0;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() = default;

    void update(VertexBufferLayoutData& layoutData) {
        if (!layoutElements.empty()) {
            const auto& prevElement = layoutElements[layoutElements.size() - 1];
            const uint32 oldOffset = (uint32)prevElement.getOffset();
            const uint32 newOffset = oldOffset + prevElement.getStride();
            layoutData.setOffset(newOffset);
        }
        stride += layoutData.getStride();
        layoutElements.push_back(layoutData);
    }

    inline uint32 getStride() const { return stride; }
    inline std::vector<VertexBufferLayoutData> getLayoutElements() const { return layoutElements; }

private:
    std::vector<VertexBufferLayoutData> layoutElements;
    uint32 stride = 0u;
};

class GLVertexBuffer : public VertexBuffer {
public:
    GLVertexBuffer(const void* data, const uint32 numBytess);

    ~GLVertexBuffer() override;

    void bind() const override;
    void unbind() const override;

    void setVertexData(const void* data, const uint32 numBytes) override;

    void setBufferLayout(const VertexBufferLayout& layoutData) override { layout = layoutData; }
    inline const VertexBufferLayout& getLayout() const override { return layout; }

private:
    uint32 vboId;
    VertexBufferLayout layout;
};

}  // namespace jupiter

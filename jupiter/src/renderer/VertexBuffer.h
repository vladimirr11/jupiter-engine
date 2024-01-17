#pragma once

// C++ system includes
#include <vector>
#include <array>
#include <initializer_list>

// Own includes
#include "base/Assert.h"

namespace jupiter {

enum VertexDataType { None, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Bool };

class VertexBufferLayoutData {
public:
    VertexBufferLayoutData() = default;

    VertexBufferLayoutData(const VertexDataType type_, bool normalized_ = false)
        : type(type_), normalized(normalized_) {
        // Look up tables used to extract the respective count and stride by given shader data type
        static const std::array vertexDataTypeLookUpCounts{0u, 1u, 2u, 3u, 4u, 1u, 2u, 3u, 4u, 1u};
        static const std::array vertexDataTypeLookUpStrides{0u, 4u, 8u,  12u, 16u,
                                                            4u, 8u, 12u, 16u, 1u};
        count = vertexDataTypeLookUpCounts[type];
        stride = vertexDataTypeLookUpStrides[type];
    }

    inline uint32 getCount() const { return count; }
    inline uint32 getStride() const { return stride; }

    inline VertexDataType getType() const {
        jAssertExpr(type != VertexDataType::None);
        return type;
    }

    inline bool isNormalized() const { return normalized; }

    inline uint32 getOffset() const { return offset; }
    inline void setOffset(const uint32 newOffset) { offset = newOffset; }

private:
    VertexDataType type = VertexDataType::None;
    bool normalized = false;
    uint32 count = 0;
    uint32 stride = 0;
    uint32 offset = 0;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() = default;

    VertexBufferLayout(const std::initializer_list<VertexBufferLayoutData>& layoutData)
        : layoutElements(layoutData) {
        size_t offset = 0;
        for (auto& element : layoutElements) {
            element.setOffset(offset);
            offset += element.getStride();
            stride += element.getStride();
        }
    }

    void update(VertexBufferLayoutData& layoutData) {
        if (!layoutElements.empty()) {
            const auto& prevElement = layoutElements[layoutElements.size() - 1];
            const uint32 oldOffset = prevElement.getOffset();
            const uint32 newOffset = oldOffset + prevElement.getStride();
            layoutData.setOffset(newOffset);
        }
        stride += layoutData.getStride();
        layoutElements.push_back(layoutData);
    }

    inline uint32 getStride() const { return stride; }
    inline std::vector<VertexBufferLayoutData> getLayoutElements() const { return layoutElements; }
    inline bool hasLayout() const { return !layoutElements.empty(); }

private:
    std::vector<VertexBufferLayoutData> layoutElements;
    uint32 stride = 0u;
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setVertexData(const void* data, const uint32 numBytes) = 0;

    virtual void setBufferLayout(const VertexBufferLayout& layout) = 0;
    virtual const VertexBufferLayout& getLayout() const = 0;
    virtual uint32 getVerticesCount() const = 0;

    static SharedPtr<VertexBuffer> create(const void* data, const uint32 numBytes);
    static SharedPtr<VertexBuffer> create(const int32 numBytes);
};

}  // namespace jupiter

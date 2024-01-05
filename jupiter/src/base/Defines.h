#pragma once

// C++ system includes
#include <memory>

#define DEBUG

// Jupiter supports only Windows for now
#ifdef JUPITER_PLATFORM_WINDOWS
#define GRAPHICS_API_OPENGL
#endif

// Debug mode macros
#ifdef DEBUG
#define JUPITER_ASSERTION_ENABLED
#endif  // DEBUG

// Jupiter primitive data types aliases
// Unsigned intigers
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed intigers
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

// Floats
typedef float float32;
typedef double float64;

namespace jupiter {

static constexpr uint32 PLATFORM_CACHE_LINE_SIZE = 64;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr UniquePtr<T> newUniquePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr SharedPtr<T> newSharedPtr(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}  // namespace jupiter

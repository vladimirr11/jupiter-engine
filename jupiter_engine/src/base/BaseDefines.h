#pragma once

// C++ system includes
#include <memory>

// Export/import jupiter api
#ifdef JUPITER_PLATFORM_WINDOWS
#define PLATFORM_CACHE_LINE_SIZE 64
#ifdef JUPITER_BUILD_DLL
#define JUPITER_API __declspec(dllexport)
#else
#define JUPITER_API __declspec(dllimport)
#endif
#else
#error jupiter engine supports only Windows
#endif

// Jupiter primitive data types aliases

// Unsigned intigers
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed intigers
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

// Floats
typedef float float32;
typedef double float64;

namespace jupiter {

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
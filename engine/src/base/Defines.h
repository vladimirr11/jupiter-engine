#pragma once

// C++ system includes
#include <memory>
#include <filesystem>

// Base difines
#define DEBUG

// Jupiter supports Windows and Linux platforms
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define JUPITER_PLATFORM_WINDOWS 1  // Windows
#define WIN32_LEAN_AND_MEAN         // Prevents Windows.h from adding unnecessary includes
#ifndef _WIN64
#error "64-bit is required on Windows"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
#define JUPITER_PLATFORM_LINUX 1  // Linux
#else
#error "Unknown platform"
#endif

// Jupiter uses OpenGL as Graphics API (for now)
#if defined(JUPITER_PLATFORM_WINDOWS) || defined(JUPITER_PLATFORM_LINUX)
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

// Base constants
static constexpr uint32 PLATFORM_CACHE_LINE_SIZE = 64;

// Base aliases
using FilesysPath = std::filesystem::path;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using UniqueArrPtr = std::unique_ptr<T[]>;

template <typename T, typename... Args>
constexpr UniquePtr<T> newUniquePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr UniqueArrPtr<T> newUniqueArrPtr(const uint64 size, Args&&... args) {
    return std::make_unique<T[]>(size, std::forward<Args>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using SharedArrPtr = std::shared_ptr<T[]>;

template <typename T, typename... Args>
constexpr SharedPtr<T> newSharedPtr(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
constexpr SharedArrPtr<T> newSharedArrPtr(const uint64 size, Args&&... args) {
    return SharedArrPtr<T>(new T[size]{std::forward<Args>(args)...});
}

}  // namespace jupiter

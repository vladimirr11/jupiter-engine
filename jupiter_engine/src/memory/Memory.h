#pragma once

// C++ system includes
#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace jupiter {

template <typename T>
inline T* allocAligned(const size_t numBytes, const size_t alignment) {
    return reinterpret_cast<T*>(_aligned_malloc(numBytes, alignment));
}

template <typename T>
inline void freeAligned(T* ptr) {
    if (!ptr) return;
    _aligned_free((void*)ptr);
}

template <typename T>
inline T* zeroMemory(T* memoryBlock, const int64_t blockSize) {
    return reinterpret_cast<T*>(memset((void*)memoryBlock, 0, blockSize));
}

inline size_t calcPadding(const size_t address, const uint8_t alignment) {
    return (~address + 1) & (alignment - 1);
}

}  // namespace jupiter
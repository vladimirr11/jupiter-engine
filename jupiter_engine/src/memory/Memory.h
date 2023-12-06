#pragma once

// C++ system includes
#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace jupiter {

template <typename T>
inline T* allocAligned(const uint64 numBytes, const uint64 alignment) {
    return reinterpret_cast<T*>(_aligned_malloc(numBytes, alignment));
}

template <typename T>
inline void freeAligned(T* ptr) {
    if (!ptr)
        return;
    _aligned_free((void*)ptr);
}

template <typename T>
inline T* zeroMemory(T* memoryBlock, const int64 blockSize) {
    return reinterpret_cast<T*>(memset((void*)memoryBlock, 0, blockSize));
}

template <typename T, typename... Args>
inline T* placeAt(T* atAddress, Args&&... args) {
    return reinterpret_cast<T*>(new (atAddress) T(std::forward<Args&&>(args)...));
}

inline uint64 calcPadding(const uint64 address, const uint8 alignment) {
    return (~address + 1) & (alignment - 1);
}

}  // namespace jupiter
#pragma once

// C++ system includes
#include <cstdint>
#include <iostream>

// Own includes
#include "base/BaseDefines.h"
#include "base/Assert.h"
#include "Memory.h"
#include "events/KeyboardEvents.h"

namespace jupiter {

class alignas(PLATFORM_CACHE_LINE_SIZE) LinearAllocator {
public:
    LinearAllocator() = delete;

    explicit LinearAllocator(const size_t memSize_);

    LinearAllocator(const LinearAllocator&) = delete;
    LinearAllocator& operator=(const LinearAllocator&) = delete;

    ~LinearAllocator() { destroy(); }

    /// @brief Returns a pointer to the next free aligned address for type T
    template <typename T>
    T* alloc(const int32_t objectCount = 1);

    /// @brief Constructs in-place an object of type T at the next free aligned
    /// memory address and returns a pointer to it
    template <typename T, typename... Args>
    T* create(Args&&... args);

    /// @brief Constructs in-place an object of type T at _atAddress_ address
    /// and returns a pointer to it
    template <typename T, typename... Args>
    T* create(T* atAddress, Args&&... args);

    /// @brief Zeros out the owning memory block
    void clear();

private:
    /// @brief Deletes the underlying memory block
    void destroy();

private:
    uint8_t* memory = nullptr;  ///< Pointer to the beginning of the owned memory
    size_t usedMemory = 0;      ///< Amount of memory used by the allocatpr
    const size_t memSize;       ///< The size in bytes of the allocated memory block
};

LinearAllocator::LinearAllocator(const size_t memSize_) : memSize(memSize_) {
    memory = allocAligned<uint8_t>(memSize, PLATFORM_CACHE_LINE_SIZE);
    jAssertPtr(memory);
}

template <typename T>
T* LinearAllocator::alloc(const int32_t objectCount) {
    if (usedMemory + (objectCount * sizeof(T)) > memSize) {
        const size_t remainingBytes = memSize - usedMemory;
        JLOG_ERROR("Requsted object count exeeds the amount of free memory. Remaining bytes {}\n",
                   remainingBytes);
        return nullptr;
    }

    size_t nextFreeAddress = (size_t)memory + usedMemory;
    const size_t padding = calcPadding(nextFreeAddress, alignof(T));
    nextFreeAddress += padding;
    usedMemory += objectCount * sizeof(T) + padding;

    return reinterpret_cast<T*>(nextFreeAddress);
}

template <typename T, typename... Args>
T* LinearAllocator::create(Args&&... args) {
    T* baseAddress = alloc<T>();
    jAssertPtr(baseAddress);
    return new (baseAddress) T(std::forward<Args&&>(args)...);
}

template <typename T, typename... Args>
T* LinearAllocator::create(T* atAddress, Args&&... args) {
    return new (atAddress) T(std::forward<Args&&>(args)...);
}

void LinearAllocator::clear() {
    memory = zeroMemory(memory, memSize);
    usedMemory = 0;
}

void LinearAllocator::destroy() { freeAligned(memory); }

}  // namespace jupiter

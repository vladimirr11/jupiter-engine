#pragma once

// Own includes
#include "base/Assert.h"
#include "Memory.h"

namespace jupiter {

class alignas(PLATFORM_CACHE_LINE_SIZE) LinearAllocator {
public:
    LinearAllocator() = delete;

    explicit LinearAllocator(const uint64 memSize_);

    LinearAllocator(const LinearAllocator&) = delete;
    LinearAllocator& operator=(const LinearAllocator&) = delete;

    ~LinearAllocator() { destroy(); }

    /// @brief Returns a pointer to the next free aligned address for type T
    template <typename T>
    T* alloc(const int32 objectCount = 1);

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
    uint8* memory = nullptr;  ///< Pointer to the beginning of the owned memory
    uint64 usedMemory = 0;    ///< Amount of memory used by the allocatpr
    const uint64 memSize;     ///< The size in bytes of the allocated memory block
};

template <typename T>
T* LinearAllocator::alloc(const int32 objectCount) {
    if (usedMemory + (objectCount * sizeof(T)) > memSize) {
        const uint64 remainingBytes = memSize - usedMemory;
        JLOG_ERROR("Requsted object count exeeds the amount of free memory. Remaining bytes {}\n",
                   remainingBytes);
        return nullptr;
    }

    uint64 nextFreeAddress = (uint64)memory + usedMemory;
    const uint64 padding = calcPadding(nextFreeAddress, alignof(T));
    nextFreeAddress += padding;
    usedMemory += objectCount * sizeof(T) + padding;

    return reinterpret_cast<T*>(nextFreeAddress);
}

template <typename T, typename... Args>
T* LinearAllocator::create(Args&&... args) {
    T* baseAddress = alloc<T>();
    jAssertPtr(baseAddress);
    return placeAt(baseAddress, std::forward<Args&&>(args)...);
}

template <typename T, typename... Args>
T* LinearAllocator::create(T* atAddress, Args&&... args) {
    return placeAt(atAddress, std::forward<Args&&>(args)...);
}

// Global linear allocator for all input events
extern UniquePtr<LinearAllocator> gLinearAllocator;

}  // namespace jupiter

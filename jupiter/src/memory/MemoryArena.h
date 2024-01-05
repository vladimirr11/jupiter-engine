#pragma once

// Own includes
#include "base/Assert.h"
#include "memory/MemoryUtils.h"

namespace jupiter {

class alignas(PLATFORM_CACHE_LINE_SIZE) MemoryArena {
public:
    MemoryArena() = delete;

    explicit MemoryArena(const uint64 memSize_);

    MemoryArena(const MemoryArena&) = delete;
    MemoryArena& operator=(const MemoryArena&) = delete;

    ~MemoryArena() { destroy(); }

    template <typename T>
    T* alloc(const int32 objectCount = 1);

    template <typename T, typename... Args>
    T* create(Args&&... args);

    template <typename T, typename... Args>
    T* create(T* atAddress, Args&&... args);

    uint64 getUsedMemory() const { return usedMemory; }

    void clear();

private:
    void destroy();

private:
    uint8* memory = nullptr;  ///< Pointer to the beginning of the owned memory
    uint64 usedMemory = 0;    ///< Amount of memory used by the allocatpr
    const uint64 memSize;     ///< The size in bytes of the allocated memory block
};

template <typename T>
T* MemoryArena::alloc(const int32 objectCount) {
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
T* MemoryArena::create(Args&&... args) {
    T* baseAddress = alloc<T>();
    jAssertPtr(baseAddress);
    return placeAt(baseAddress, std::forward<Args&&>(args)...);
}

template <typename T, typename... Args>
T* MemoryArena::create(T* atAddress, Args&&... args) {
    return placeAt(atAddress, std::forward<Args&&>(args)...);
}

// Global memory arena for all input events
extern UniquePtr<MemoryArena> gMemoryArena;

}  // namespace jupiter

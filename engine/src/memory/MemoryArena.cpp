// Jpch
#include "Jpch.h"

// Own includes
#include "memory/MemoryArena.h"

namespace jupiter {

UniquePtr<MemoryArena> gMemoryArena = nullptr;

MemoryArena::MemoryArena(const uint64 memSize_) : memSize(memSize_) {
    memory = allocAligned<uint8_t>(memSize, PLATFORM_CACHE_LINE_SIZE);
    jAssertPtr(memory);
    JLOG_INFO("Memory Arena allocated with {} bytes", memSize);
}

void MemoryArena::clear() {
    memory = zeroMemory(memory, memSize);
    usedMemory = 0;
}

void MemoryArena::destroy() { freeAligned(memory); }

}  // namespace jupiter

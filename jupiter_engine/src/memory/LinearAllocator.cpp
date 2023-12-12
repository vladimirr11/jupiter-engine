// Jpch
#include "Jpch.h"

// Own includes
#include "LinearAllocator.h"

namespace jupiter {

UniquePtr<LinearAllocator> gLinearAllocator = nullptr;

LinearAllocator::LinearAllocator(const uint64 memSize_) : memSize(memSize_) {
    memory = allocAligned<uint8_t>(memSize, PLATFORM_CACHE_LINE_SIZE);
    jAssertPtr(memory);
}

void LinearAllocator::clear() {
    memory = zeroMemory(memory, memSize);
    usedMemory = 0;
}

void LinearAllocator::destroy() { freeAligned(memory); }

}  // namespace jupiter

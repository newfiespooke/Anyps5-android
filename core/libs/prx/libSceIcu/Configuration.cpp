#include "prx/libSceIcu/libSceIcu.hpp"
#include "prx/libc/include/General.hpp"
#include "unicode/uclean.h"
#include <cstdint>
#include <mutex>

namespace {
bool Failure(const std::int32_t* status) {
    if (!status) APS5_INVALID_ARG_EX;
    return *status > 0;
}
constexpr std::int32_t IllegalArgument = 1;

struct MemoryFunctions {
    const void* context = nullptr;
    Icu::MemoryAllocate allocate = nullptr;
    Icu::MemoryReallocate reallocate = nullptr;
    Icu::MemoryFree release = nullptr;
};

std::mutex MemoryLock;
MemoryFunctions Memory;
MemoryFunctions Snapshot() {
    const std::lock_guard lock(MemoryLock);
    return Memory;
}

void* U_CALLCONV Allocate(const void*, std::size_t size) {
    const auto memory = Snapshot();
    return memory.allocate(memory.context, size);
}

void* U_CALLCONV Reallocate(const void*, void* pointer, std::size_t size) {
    const auto memory = Snapshot();
    return memory.reallocate(memory.context, pointer, size);
}

void U_CALLCONV Release(const void*, void* pointer) {
    const auto memory = Snapshot();
    memory.release(memory.context, pointer);
}

}

extern "C" {

void APS5_VABI u_setMemoryFunctions_nid_postfix(const void* context, Icu::MemoryAllocate allocate, Icu::MemoryReallocate reallocate,
                                                Icu::MemoryFree release, std::int32_t* status) {
    if (Failure(status)) return;
    if (!allocate || !reallocate || !release) {
        *status = IllegalArgument;
        return;
    }
    const std::lock_guard lock(MemoryLock);
    auto nativeStatus = static_cast<UErrorCode>(*status);
    u_setMemoryFunctions(nullptr, Allocate, Reallocate, Release, &nativeStatus);
    *status = nativeStatus;
    if (U_SUCCESS(nativeStatus)) Memory = {context, allocate, reallocate, release};
}


void APS5_VABI u_cleanup_nid_postfix() {
    u_cleanup();
    {
        const std::lock_guard lock(MemoryLock);
        Memory = {};
    }
}

}

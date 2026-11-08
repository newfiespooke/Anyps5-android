#pragma once
#include "prx/libc/include/general/VabiMacros.hpp"
#include <cstddef>
#include <cstdint>

namespace Icu {
using MemoryAllocate = void* (APS5_VABI*)(const void*, std::size_t);
using MemoryReallocate = void* (APS5_VABI*)(const void*, void*, std::size_t);
using MemoryFree = void (APS5_VABI*)(const void*, void*);
} // namespace Icu

extern "C" {
void APS5_VABI u_setMemoryFunctions_nid_postfix(const void*, Icu::MemoryAllocate, Icu::MemoryReallocate, Icu::MemoryFree, std::int32_t*);
void APS5_VABI u_cleanup_nid_postfix();
}

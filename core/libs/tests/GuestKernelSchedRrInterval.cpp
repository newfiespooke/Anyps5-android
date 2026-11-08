#include "prx/libkernel/include/Api.hpp"
#include "prx/libc/include/Api.hpp"
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <stdexcept>

namespace {

constexpr int SentinelErrno = 42;
constexpr int ErrnoInval = 22;
constexpr int ErrnoSrch = 3;

void Require(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "Requirement failed: %s (errno=%d)\n", message, *__error_nid_postfix());
        std::abort();
    }
}

void AuditSchedRrGetInterval() {
    struct timespec tp;
    *__error_nid_postfix() = SentinelErrno;
    int res = sched_rr_get_interval_nid_postfix(0, &tp);
    Require(res == 0 || res == -1, "sched_rr_get_interval must return valid status");

    constexpr std::array<int, 4> invalidPids{
        -1,
        -999,
        999999,
        std::numeric_limits<int>::max()
    };

    for (const int pid : invalidPids) {
        *__error_nid_postfix() = SentinelErrno;
        Require(sched_rr_get_interval_nid_postfix(pid, &tp) == -1, "sched_rr_get_interval with invalid pid must fail");
        Require(*__error_nid_postfix() == ErrnoSrch, "sched_rr_get_interval with invalid pid must set errno to ESRCH");
    }

    *__error_nid_postfix() = SentinelErrno;
    Require(sched_rr_get_interval_nid_postfix(0, nullptr) == -1, "sched_rr_get_interval with null timespec must fail");
    Require(*__error_nid_postfix() == ErrnoInval, "sched_rr_get_interval with null timespec must set errno to EINVAL");
}

} // namespace

int main() {
    AuditSchedRrGetInterval();
    return 0;
}

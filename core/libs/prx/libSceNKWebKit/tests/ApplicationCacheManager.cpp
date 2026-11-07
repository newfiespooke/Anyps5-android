#include "prx/libc/include/general/VabiMacros.hpp"
#include "prx/libSceNKWebKit/include/WebKitValueExports.hpp"
#include "prx/libSceNKWebKit/src/Types.hpp"

#include <cstdio>
#include <cstdlib>
#include <source_location>
#include <stdexcept>

namespace {

void Require(bool condition, std::source_location location = std::source_location::current()) {
    if (!condition) {
        std::fprintf(stderr, "ApplicationCacheManager check failed at line %u\n", location.line());
        std::abort();
    }
}

template<class Function>
void RequireInvalidArgument(Function function) {
    bool threw = false;
    try {
        function();
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    Require(threw);
}

bool callbackCalled = false;
void OnOrigins(const void* arrayRef, const void* errorRef, void* context) {
    (void)errorRef;
    (void)context;
    callbackCalled = (arrayRef != nullptr);
    if (arrayRef) {
        WKRelease(arrayRef);
    }
}

}

int main() {
    auto mgr = NKWebKit::Make<NKWebKit::ApplicationCacheManager>();
    const void* mgrRef = NKWebKit::ToRef(mgr);
    mgr->origins.push_back("example.com");

    WKApplicationCacheManagerDeleteAllEntries(mgrRef);
    Require(mgr->origins.empty());

    mgr->origins.push_back("example.org");
    auto originStr = NKWebKit::String::FromUtf8("example.org");
    const void* originRef = NKWebKit::ToRef(originStr);
    WKApplicationCacheManagerDeleteEntriesForOrigin(mgrRef, originRef);
    Require(mgr->origins.empty());
    WKApplicationCacheManagerDeleteEntriesForOrigin(mgrRef, nullptr);

    mgr->origins.push_back("example.net");
    WKApplicationCacheManagerGetApplicationCacheOrigins(mgrRef, nullptr, OnOrigins);
    Require(callbackCalled);
    WKApplicationCacheManagerGetApplicationCacheOrigins(mgrRef, nullptr, nullptr);

    RequireInvalidArgument([] { WKApplicationCacheManagerDeleteAllEntries(nullptr); });
    RequireInvalidArgument([&] { WKApplicationCacheManagerDeleteEntriesForOrigin(nullptr, originRef); });
    RequireInvalidArgument([] { WKApplicationCacheManagerGetApplicationCacheOrigins(nullptr, nullptr, OnOrigins); });

    WKRelease(originRef);
    WKRelease(mgrRef);
    return 0;
}

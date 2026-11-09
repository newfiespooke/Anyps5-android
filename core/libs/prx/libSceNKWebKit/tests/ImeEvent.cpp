#include "prx/libc/include/general/VabiMacros.hpp"
#include "prx/libSceNKWebKit/include/WebKitValueExports.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <source_location>

namespace {

void Require(bool condition, std::source_location location = std::source_location::current()) {
    if (!condition) {
        std::fprintf(stderr, "ImeEvent check failed at line %u\n", location.line());
        std::abort();
    }
}

}

int main() {
    Require(WKImeEventGetInputLanguage(nullptr) == static_cast<WKInputLanguage>(-1));
    Require(WKImeEventGetInputLanguage("") == static_cast<WKInputLanguage>(-1));
    Require(WKImeEventGetInputLanguage("unknown_XYZ") == static_cast<WKInputLanguage>(-1));

    Require(WKImeEventGetInputLanguage("en_Latn_US") == static_cast<WKInputLanguage>(2));
    Require(WKImeEventGetInputLanguage("ja_Jpan_JP") == static_cast<WKInputLanguage>(13));
    Require(WKImeEventGetInputLanguage("es_Latn_ES") == static_cast<WKInputLanguage>(3));

    auto* event = WKImeEventMake(static_cast<WKImeEventType>(6), "hello", 42);
    Require(event != nullptr);
    WKImeEventRelease(event);

    auto* nullTextEvent = WKImeEventMake(static_cast<WKImeEventType>(0), nullptr, 0);
    Require(nullTextEvent != nullptr);
    WKImeEventRelease(nullTextEvent);
    return 0;
}

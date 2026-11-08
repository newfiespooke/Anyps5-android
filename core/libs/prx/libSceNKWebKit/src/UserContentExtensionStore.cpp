#include "prx/libSceNKWebKit/include/WebKitValueExports.hpp"
#include "prx/libSceNKWebKit/src/Configuration.hpp"
#include "prx/libSceNKWebKit/src/Types.hpp"

extern "C" {

void APS5_VABI WKUserContentExtensionStoreCompile(const void* storeRef, const void* identifierRef, const void* jsonSourceRef, void* context, void (*callback)(const void*, std::uint32_t, void*)) {
    auto* store = NKWebKit::Cast<NKWebKit::ContentRuleListStore>(storeRef, __func__);
    const auto* identifier = NKWebKit::Cast<NKWebKit::String>(identifierRef, __func__);
    (void)NKWebKit::Cast<NKWebKit::String>(jsonSourceRef, __func__);

    auto filter = NKWebKit::Make<NKWebKit::ContentRuleList>();
    const void* filterRef = NKWebKit::ToRef(filter);
    store->filters[identifier->characters] = NKWebKit::Retained<NKWebKit::Object>::Share(filter.Get());

    if (callback) {
        callback(filterRef, 0, context);
    }
}

void APS5_VABI WKUserContentExtensionStoreLookup(const void* storeRef, const void* identifierRef, void* context, void (*callback)(const void*, std::uint32_t, void*)) {
    auto* store = NKWebKit::Cast<NKWebKit::ContentRuleListStore>(storeRef, __func__);
    const auto* identifier = NKWebKit::Cast<NKWebKit::String>(identifierRef, __func__);

    auto it = store->filters.find(identifier->characters);
    if (it != store->filters.end()) {
        if (callback) {
            callback(NKWebKit::ToRef(it->second), 0, context);
        }
    } else {
        if (callback) {
            callback(nullptr, 1, context);
        }
    }
}

}

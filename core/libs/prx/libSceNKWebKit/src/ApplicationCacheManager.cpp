#include "prx/libSceNKWebKit/include/WebKitValueExports.hpp"
#include "prx/libSceNKWebKit/src/Types.hpp"

extern "C" {

void APS5_VABI WKApplicationCacheManagerDeleteAllEntries(const void* managerRef) {
    auto* manager = NKWebKit::Cast<NKWebKit::ApplicationCacheManager>(managerRef, __func__);
    manager->DeleteAll();
}

void APS5_VABI WKApplicationCacheManagerDeleteEntriesForOrigin(const void* managerRef, const void* originRef) {
    auto* manager = NKWebKit::Cast<NKWebKit::ApplicationCacheManager>(managerRef, __func__);
    if (!originRef) {
        return;
    }
    const auto* str = NKWebKit::CastOrNull<NKWebKit::String>(originRef, __func__);
    if (str) {
        manager->DeleteForOrigin(str->Utf8());
    } else {
        manager->DeleteAll();
    }
}

void APS5_VABI WKApplicationCacheManagerGetApplicationCacheOrigins(const void* managerRef, void* context, void (*callback)(const void*, const void*, void*)) {
    auto* manager = NKWebKit::Cast<NKWebKit::ApplicationCacheManager>(managerRef, __func__);
    if (callback) {
        auto array = NKWebKit::Make<NKWebKit::Array>();
        for (const auto& o : manager->origins) {
            array->elements.push_back(NKWebKit::String::FromUtf8(o.c_str()));
        }
        callback(NKWebKit::ToRef(array), nullptr, context);
    }
}

}

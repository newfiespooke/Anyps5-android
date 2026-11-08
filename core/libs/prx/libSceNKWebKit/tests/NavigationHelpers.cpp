#include "prx/libSceNKWebKit/src/Types.hpp"
#include "prx/libSceNKWebKit/src/NavigationData.hpp"
#include "prx/libSceNKWebKit/include/WebKitValueExports.hpp"
#include <cassert>
#include <stdexcept>

static void RequireInvalidArgument(auto&& callable) {
    try {
        callable();
        assert(false);
    } catch (const std::invalid_argument&) {
    }
}

int main() {
    RequireInvalidArgument([] {
        WKNavigationActionShouldPerformDownload(nullptr);
    });
    RequireInvalidArgument([] {
        WKNavigationResponseCanShowMIMEType(nullptr);
    });
    RequireInvalidArgument([] {
        WKNavigationDataCopyOriginalRequest(nullptr);
    });

    auto action = NKWebKit::Make<NKWebKit::NavigationAction>(true);
    assert(WKNavigationActionShouldPerformDownload(NKWebKit::ToRef(action)) == true);

    auto actionNo = NKWebKit::Make<NKWebKit::NavigationAction>(false);
    assert(WKNavigationActionShouldPerformDownload(NKWebKit::ToRef(actionNo)) == false);

    auto response = NKWebKit::Make<NKWebKit::NavigationResponse>(true);
    assert(WKNavigationResponseCanShowMIMEType(NKWebKit::ToRef(response)) == true);

    auto responseNo = NKWebKit::Make<NKWebKit::NavigationResponse>(false);
    assert(WKNavigationResponseCanShowMIMEType(NKWebKit::ToRef(responseNo)) == false);

    auto data = NKWebKit::Make<NKWebKit::NavigationData>(nullptr, std::nullopt, std::string("https://example.com/item"));
    auto* req = WKNavigationDataCopyOriginalRequest(NKWebKit::ToRef(data));
    assert(req != nullptr);
    assert(WKGetTypeID(req) == WKURLRequestGetTypeID());
    WKRelease(req);

    auto dataEmpty = NKWebKit::Make<NKWebKit::NavigationData>();
    assert(WKNavigationDataCopyOriginalRequest(NKWebKit::ToRef(dataEmpty)) == nullptr);

    return 0;
}

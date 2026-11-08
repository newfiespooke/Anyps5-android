#include "prx/libSceFont/include/Api.hpp"
#include "prx/libSceFont/include/FontTypes.hpp"
#include "prx/libSceFontFt/include/Api.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void Check(bool value, int line) {
    if (!value) {
        std::fprintf(stderr, "Font support check failed at line %d\n", line);
        std::abort();
    }
}
#define Require(value) Check((value), __LINE__)

int main() {
    const FontFtGlyphSelection* selection = sceFontSelectGlyphsFt(0);
    Require(selection != nullptr);
    const auto* selectionTags = reinterpret_cast<const std::uint16_t*>(selection);
    Require(selectionTags[0] == 0x0F1F);
    Require(selectionTags[1] == 0xF200);
    Require(selectionTags[2] == 0x0F03);
    Require(selectionTags[3] == 0xF8F0);
    Require(sceFontSelectGlyphsFt(1) == nullptr);
    Require(sceFontSelectGlyphsFt(-1) == nullptr);

    alignas(16) std::uint16_t badTag[4] = {0x0F1E, 0xF200, 0x0F03, 0xF8F0};
    alignas(16) std::uint16_t badKind[4] = {0x0F1F, 0xF200, 0x0F02, 0xF8F0};
    alignas(16) std::uint16_t otherTable[4] = {0x0F1F, 0xF200, 0x0F03, 0xF8F0};
    alignas(16) std::uint16_t thirdTable[4] = {0x0F1F, 0xF200, 0x0F03, 0xF8F0};
    Require(sceFontSupportGlyphs(nullptr) == SCE_FONT_ERROR_INVALID_PARAMETER);
    Require(sceFontSupportGlyphs(reinterpret_cast<const FontGlyphSupport*>(badTag)) == SCE_FONT_ERROR_INVALID_PARAMETER);
    Require(sceFontSupportGlyphs(reinterpret_cast<const FontGlyphSupport*>(badKind)) == SCE_FONT_ERROR_FATAL);

    Require(sceFontSupportGlyphs(reinterpret_cast<const FontGlyphSupport*>(selection)) == SCE_FONT_OK);
    Require(sceFontSupportGlyphs(reinterpret_cast<const FontGlyphSupport*>(otherTable)) == SCE_FONT_OK);
    Require(sceFontSupportGlyphs(reinterpret_cast<const FontGlyphSupport*>(thirdTable)) == SCE_FONT_OK);
    Require(sceFontSupportGlyphs(reinterpret_cast<const FontGlyphSupport*>(selection)) == SCE_FONT_OK);
    std::puts("Font support registration tests passed");
}

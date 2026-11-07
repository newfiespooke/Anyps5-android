#include "prx/libSceNKWebKit/include/WebKitValueExports.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string_view>

enum WKInputLanguage : int {
    InputLanguageUndefined = -1,

    INPUT_LANGUAGE_DANISH,
    INPUT_LANGUAGE_GERMAN,
    INPUT_LANGUAGE_ENGLISH_US,
    INPUT_LANGUAGE_SPANISH,
    INPUT_LANGUAGE_FRENCH,
    INPUT_LANGUAGE_ITALIAN,
    INPUT_LANGUAGE_DUTCH,
    INPUT_LANGUAGE_NORWEGIAN,
    INPUT_LANGUAGE_POLISH,
    INPUT_LANGUAGE_PORTUGUESE_PT,
    INPUT_LANGUAGE_RUSSIAN,
    INPUT_LANGUAGE_FINNISH,
    INPUT_LANGUAGE_SWEDISH,
    INPUT_LANGUAGE_JAPANESE,
    INPUT_LANGUAGE_KOREAN,
    INPUT_LANGUAGE_SIMPLIFIED_CHINESE,
    INPUT_LANGUAGE_TRADITIONAL_CHINESE,
    INPUT_LANGUAGE_PORTUGUESE_BR,
    INPUT_LANGUAGE_ENGLISH_GB,
    INPUT_LANGUAGE_TURKISH,
    INPUT_LANGUAGE_SPANISH_LATIN_AMERICA,
    INPUT_LANGUAGE_ARABIC,
    INPUT_LANGUAGE_CANADIAN_FRENCH,
    INPUT_LANGUAGE_THAI,
    INPUT_LANGUAGE_CZECH,
    INPUT_LANGUAGE_GREEK,
    INPUT_LANGUAGE_INDONESIAN,
    INPUT_LANGUAGE_VIETNAMESE,
    INPUT_LANGUAGE_ROMANIAN,
    INPUT_LANGUAGE_HUNGARIAN,
    INPUT_LANGUAGE_UKRAINIAN,

    InputLanguageCount,
};

enum WKImeEventType : int {
    Open,
    ChangeSize,
    PressClose,
    PressEnter,
    UpdatePreedit,
    ConfirmPreedit,
    InsertText,
    Backspace,
    DeleteAllBeforeCaret,
    DeleteAll,
    CaretMoveLeft,
    CaretMoveRight,
    CaretMoveUp,
    CaretMoveDown,
    StartSelection,
    EndSelection,
    SendSelectionWord,
    MoveDialog,
    GetInputText,
    SetValueToFocusedNode,
};

struct WKImeEvent {
    WKImeEventType imeEventType;
    const char* compositionString;
    int keyCode;
    int caretIndex;
};

namespace {

struct InputLanguageEntry {
    const char* attr;
    WKInputLanguage value;
};

constexpr InputLanguageEntry languageEntries[] = {
    { "da_Latn_DK",         INPUT_LANGUAGE_DANISH },
    { "da",                 INPUT_LANGUAGE_DANISH },
    { "de_Latn_DE",         INPUT_LANGUAGE_GERMAN },
    { "de",                 INPUT_LANGUAGE_GERMAN },
    { "en_Latn_US",         INPUT_LANGUAGE_ENGLISH_US },
    { "en-US",              INPUT_LANGUAGE_ENGLISH_US },
    { "en_US",              INPUT_LANGUAGE_ENGLISH_US },
    { "en",                 INPUT_LANGUAGE_ENGLISH_US },
    { "es_Latn_ES",         INPUT_LANGUAGE_SPANISH },
    { "es",                 INPUT_LANGUAGE_SPANISH },
    { "fr_Latn_FR",         INPUT_LANGUAGE_FRENCH },
    { "fr",                 INPUT_LANGUAGE_FRENCH },
    { "it_Latn_IT",         INPUT_LANGUAGE_ITALIAN },
    { "it",                 INPUT_LANGUAGE_ITALIAN },
    { "nl_Latn_NL",         INPUT_LANGUAGE_DUTCH },
    { "nl",                 INPUT_LANGUAGE_DUTCH },
    { "no_Latn_NO",         INPUT_LANGUAGE_NORWEGIAN },
    { "no",                 INPUT_LANGUAGE_NORWEGIAN },
    { "pl_Latn_PL",         INPUT_LANGUAGE_POLISH },
    { "pl",                 INPUT_LANGUAGE_POLISH },
    { "pt_Latn_BR",         INPUT_LANGUAGE_PORTUGUESE_BR },
    { "ru_Cyrl_RU",         INPUT_LANGUAGE_RUSSIAN },
    { "ru",                 INPUT_LANGUAGE_RUSSIAN },
    { "fi_Latn_FI",         INPUT_LANGUAGE_FINNISH },
    { "fi",                 INPUT_LANGUAGE_FINNISH },
    { "se_Latn_NO",         INPUT_LANGUAGE_SWEDISH },
    { "sv_Latn_SE",         INPUT_LANGUAGE_SWEDISH },
    { "sv",                 INPUT_LANGUAGE_SWEDISH },
    { "ja_Jpan_JP",         INPUT_LANGUAGE_JAPANESE },
    { "ja",                 INPUT_LANGUAGE_JAPANESE },
    { "ko_Kore_KR",         INPUT_LANGUAGE_KOREAN },
    { "ko",                 INPUT_LANGUAGE_KOREAN },
    { "zh_Hans_CN",         INPUT_LANGUAGE_SIMPLIFIED_CHINESE },
    { "zh-Hans",            INPUT_LANGUAGE_SIMPLIFIED_CHINESE },
    { "tr_Latn_TR",         INPUT_LANGUAGE_TURKISH },
    { "tr",                 INPUT_LANGUAGE_TURKISH },
    { "ar_Arab_EG",         INPUT_LANGUAGE_ARABIC },
    { "ar",                 INPUT_LANGUAGE_ARABIC },
    { "th_Thai_TH",         INPUT_LANGUAGE_THAI },
    { "th",                 INPUT_LANGUAGE_THAI },
    { "cs_Latn_CZ",         INPUT_LANGUAGE_CZECH },
    { "cs",                 INPUT_LANGUAGE_CZECH },
    { "el_Grek_GR",         INPUT_LANGUAGE_GREEK },
    { "el",                 INPUT_LANGUAGE_GREEK },
    { "id_Latn_ID",         INPUT_LANGUAGE_INDONESIAN },
    { "id",                 INPUT_LANGUAGE_INDONESIAN },
    { "vi_Latn_VN",         INPUT_LANGUAGE_VIETNAMESE },
    { "vi",                 INPUT_LANGUAGE_VIETNAMESE },
    { "ro_Latn_RO",         INPUT_LANGUAGE_ROMANIAN },
    { "ro",                 INPUT_LANGUAGE_ROMANIAN },
    { "hu_Latn_HU",         INPUT_LANGUAGE_HUNGARIAN },
    { "hu",                 INPUT_LANGUAGE_HUNGARIAN },
    { "uk_Cyrl_UA",         INPUT_LANGUAGE_UKRAINIAN },
    { "uk",                 INPUT_LANGUAGE_UKRAINIAN },
    { "en_Latn_GB",         INPUT_LANGUAGE_ENGLISH_GB },
    { "en-GB",              INPUT_LANGUAGE_ENGLISH_GB },
    { "es_Latn_419",        INPUT_LANGUAGE_SPANISH_LATIN_AMERICA },
    { "pt_Latn_PT",         INPUT_LANGUAGE_PORTUGUESE_PT },
    { "pt",                 INPUT_LANGUAGE_PORTUGUESE_PT },
    { "zh_Hant_HK",         INPUT_LANGUAGE_TRADITIONAL_CHINESE },
    { "zh_Hant_TW",         INPUT_LANGUAGE_TRADITIONAL_CHINESE },
    { "zh-Hant",            INPUT_LANGUAGE_TRADITIONAL_CHINESE },
    { "fr_Latn_CA",         INPUT_LANGUAGE_CANADIAN_FRENCH },
};

}  // namespace

extern "C" {

WKInputLanguage APS5_VABI WKImeEventGetInputLanguage(const char* languageCode) {
    if (!languageCode || !languageCode[0]) {
        return InputLanguageUndefined;
    }
    for (const auto& entry : languageEntries) {
        if (std::strcmp(languageCode, entry.attr) == 0) {
            return entry.value;
        }
    }
    return InputLanguageUndefined;
}

WKImeEvent* APS5_VABI WKImeEventMake(WKImeEventType imeEventType, const char* compositionString, int keyCode) {
    auto* imeEvent = new WKImeEvent();
    imeEvent->imeEventType = imeEventType;
    imeEvent->compositionString = compositionString;
    imeEvent->keyCode = keyCode;
    imeEvent->caretIndex = 0;
    if (compositionString) {
        imeEvent->caretIndex = static_cast<int>(std::strlen(compositionString));
    }
    return imeEvent;
}

void APS5_VABI WKImeEventRelease(WKImeEvent* imeEvent) {
    delete imeEvent;
}

}

//
// Created by murasame on 23-4-30.
//

#include <cctype>
#include <locale>
#include <algorithm>
#include "TjsLexicalAnalyzer.h"
#include "TjsToken.h"

namespace tjs_analysis {
bool IsSpaceChar(char32_t ch) {
    // Convert char32_t to a narrow character (char) if it's an ASCII whitespace character.
    if (ch <= 0x7F) {
        return std::isspace(static_cast<unsigned char>(ch)) != 0;
    }

    // For non-ASCII characters, use the std::isspace function from the <locale> header.
    std::locale loc;
    return std::isspace(static_cast<wchar_t>(ch), loc) != 0;
}


bool TjsLexicalDfa::IsIntermediateState(LexicalDfaState state) const {

    return std::any_of(std::cbegin(kIntermediateStates),
                       std::cend(kIntermediateStates),
                       [state](LexicalDfaState intermediate_state) {
                           return state == intermediate_state;
                       });
}

bool TjsLexicalDfa::IsSingleCharacterSymbol(char32_t input) const {
    return std::any_of(std::cbegin(kSingleCharacterSymbolChar),
                       std::cend(kSingleCharacterSymbolChar),
                       [input](char symbol) {
                           return input == symbol;
                       });
}

bool TjsLexicalDfa::IsBracket(char32_t input) const {
    return std::any_of(std::cbegin(kBracketChar),
                       std::cend(kBracketChar),
                       [input](char bracket) {
                           return input == bracket;
                       });
}
bool TjsLexicalDfa::IsHexChar(char32_t input) {
    return (input >= '0' && input <= '9') ||
           (input >= 'a' && input <= 'f') ||
           (input >= 'A' && input <= 'F');
}

bool TjsLexicalDfa::MayBeIdentifierOrKeyword(char32_t ch) const {
    if (IsSingleCharacterSymbol(ch))
        return false;
    if (IsBracket(ch))
        return false;
    if (IsSpaceChar(ch))
        return false;

    bool is_legal = UnicodeIsInRange(ch, 0x0000, 0x007F);  // ASCII
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0080, 0x00FF);  // Latin-1 Supplement
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0100, 0x017F);  // Latin Extended-A
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0180, 0x024F);  // Latin Extended-B
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0250, 0x02AF);  // IPA Extensions
    is_legal = is_legal || UnicodeIsInRange(ch, 0x02B0, 0x02FF);  // Spacing Modifier Letters
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0370, 0x03FF);  // Greek and Coptic
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0400, 0x04FF);  // Cyrillic
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0530, 0x058F);  // Armenian
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0590, 0x05FF);  // Hebrew
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0600, 0x06FF);  // Arabic
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0700, 0x074F);  // Syriac
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0750, 0x077F);  // Arabic Supplement
    is_legal = is_legal || UnicodeIsInRange(ch, 0x0780, 0x07FF);  // African
    is_legal = is_legal || UnicodeIsInRange(ch, 0x1D00, 0x1D7F);  // Phonetic Extensions
    is_legal = is_legal || UnicodeIsInRange(ch, 0x2200, 0x22FF);  // Mathematical Operators
    is_legal = is_legal || UnicodeIsInRange(ch, 0x2300, 0x23FF);  // Miscellaneous Technical
    is_legal = is_legal || UnicodeIsInRange(ch, 0x2400, 0x243F);  // Control Pictures
    is_legal = is_legal || UnicodeIsInRange(ch, 0x2460, 0x24FF);  // Enclosed Alphanumerics
    is_legal = is_legal || UnicodeIsInRange(ch, 0x3200, 0x32FF);  // Enclosed CJK Letters and Months
    is_legal = is_legal || UnicodeIsInRange(ch, 0x4E00, 0x9FFF);  // CJK Unified Ideographs

    return is_legal;
}

bool TjsLexicalDfa::Accept() const {
    return (current_state_ != kReject) && (current_state_ != kStart)
            && !IsIntermediateState(current_state_);
}
bool TjsLexicalDfa::Reject() const {
    return current_state_ == kReject;
}
LexicalDfaState TjsLexicalDfa::Transition(LexicalDfaState state, char32_t input) const {
    if (state == kStart)
        return TransitionHandle_kStart(input);
    if (state == kReject) return kReject;

    if (state == kNotDecimalOrFloat)
        return TransitionHandle_kNotDecimalOrFloat(input);

    // when input is blank, Reject it, except for the kBlank or start state.
    if (state == kBlank) {
        if (IsSpaceChar(input)) return kBlank;
        return kReject;
    }

    if (state == kIdentifierOrKeyword) {
        // there must not be a special symbol in identifier.
        if (IsSingleCharacterSymbol(input)) return kReject;

        // there must not be a bracket in identifier.
        if (IsBracket(input)) return kReject;

        if (MayBeIdentifierOrKeyword(input)) return kIdentifierOrKeyword;

    }

    // Decimal
    if (state == kDecimalInteger) {
        if (input >= '0' && input <= '9') return kDecimalInteger;
        if (input == '.') return kDecimalFloat;
        if (input == 'e' || input == 'E') return kDecimalFloat;
        return kReject;
    }
    if (state == kDecimalFloat) {
        if (input >= '0' && input <= '9') return kDecimalFloat;
        if (input == 'e' || input == 'E') return kDecimalFloat;
        return kReject;
    }

    // Binary
    if (state == kBinaryInteger) {
        if (input == '0' || input == '1') return kBinaryInteger;
        if (input == '.') return kBinaryFloat;
        return kReject;
    }
    if (state == kBinaryFloat) {
        if (input == '0' || input == '1') return kBinaryFloat;
        return kReject;
    }

    // Octal
    if (state == kOctalInteger) {
        if (input >= '0' && input <= '7') return kOctalInteger;
        if (input == '.') return kOctalFloat;
        return kReject;
    }
    if (state == kOctalFloat) {
        if (input >= '0' && input <= '7') return kOctalFloat;
        return kReject;
    }

    // Hex
    if (state == kHexInteger) {
        if (IsHexChar(input)) return kHexInteger;
        if (input == '.') return kHexFloat;
        return kReject;
    }
    if (state == kHexFloat) {
        if (IsHexChar(input)) return kHexFloat;
        return kReject;
    }

    // special symbols can be multiple characters.
    if (state == kSpecialSymbol) {
        return IsSingleCharacterSymbol(input)? kSpecialSymbol : kReject;
    }

    // brackets can not be multiple characters.
    if (state == kBracket) return kReject;

    // if all above conditions are not satisfied, Reject it.
    return kReject;
}

LexicalDfaState TjsLexicalDfa::TransitionHandle_kStart(char32_t input) const {
    // when starter is a blank:
    if (IsSpaceChar(input)) {
        return kBlank;
    }

    // when starter is a digit:
    // when starter is "0", it may be a binary, octal or hex integer (or float),
    // or a decimal float.
    else if (input == '0') {
        return kNotDecimalOrFloat;
    }
    // when starter is '1' to '9', it must be a decimal integer (or float).
    else if (input >= '1' && input <= '9') {
        return kDecimalInteger;
    }

    // when starter is a single character symbol or bracket:
    else if (IsSingleCharacterSymbol(input)) {
        return kSpecialSymbol;
    }
    else if (IsBracket(input)) {
        return kBracket;
    }

    // when starter is a letter:
    else if (MayBeIdentifierOrKeyword(input)) {
        return kIdentifierOrKeyword;
    }

    // this is an error.
    return kReject;
}

LexicalDfaState TjsLexicalDfa::TransitionHandle_kNotDecimalOrFloat(char32_t input) {
    // when first character is '0', we can determine whether it is
    // a binary, octal or hex integer in the second character.

    if (input == 'b' || input == 'B') {
        return kBinaryInteger;
    }
    if (input >= '1' && input <= '7') {
        return kOctalInteger;
    }
    if (input == 'x' || input == 'X') {
        return kHexInteger;
    }
    if (input == '.') {
        return kDecimalFloat;
    }

    return kReject;
}

TjdUnknownToken TjsIsIdentifierOrKeyWord(const std::u32string& input) {
    using std::make_unique;
    auto identifier_ptr =  make_unique<TjsIdentifierToken>(input);
    TjdUnknownToken result = {true, nullptr, nullptr};
    for (int i = 0; i < sizeof(kTjsKeywords) / sizeof(kTjsKeywords[0]); ++i) {
        if (input == kTjsKeywords[i]) {
            result.is_identifier = false;
            auto keyword = make_unique<TjsNoAttributeToken>(kTjsKeywordsMapper[i]);
            result.tjs_no_attribute_token_value = std::move(keyword);
            return result;
        }
    }
    auto identifier = make_unique<TjsIdentifierToken>(input);
    result.tjs_identifier_token_value = std::move(identifier);
    return result;
}

} // tjs_analysis
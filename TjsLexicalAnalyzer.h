//
// Created by murasame on 23-4-30.
//

#ifndef TJS2JSON_TJS_LEXICAL_ANALYZER_H
#define TJS2JSON_TJS_LEXICAL_ANALYZER_H

#include <utility>
#include <map>
#include "AbstractDfa.h"

namespace tjs_analysis {

enum LexicalDfaState {
    kStart,     // start state
    kReject,    // Reject state

    kBlank,     // space, tab, newline, etc.

    kSpecialSymbol,
    kBracket,
    // special symbol state, allow these tokens:
    // - all single character tokens
    // - all brackets
    // - all double character tokens
    // - all triple character tokens
    // - all longer character tokens (actually, there is only one: >>>=)

    kNotDecimalOrFloat,
    // when input a "0", it may be a binary, octal or hex integer (or float),
    // or a decimal float.
    // this state is not a final state.

    kBinaryInteger,
    kBinaryFloat,
    // in TJS2, binary integer should be like this:
    // 0b10101010
    // start with 0b, and then followed by a sequence of 0 and 1
    // in TJS2, binary float should be like this:
    // 0b10101010.10101010
    // start with 0b, and then followed by a sequence of 0 and 1,
    // and then followed by a dot, and then followed by a sequence of 0 and 1

    kOctalInteger,
    kOctalFloat,
    // in TJS2, octal integer should be like this:
    // 01234567
    // start with 0, and then followed by a sequence of 0 to 7
    // in TJS2, octal float should be like this:
    // 01234567.01234567

    kDecimalInteger,
    kDecimalFloat,
    // in TJS2, decimal integer should be like this:
    // 1234567890
    // start with a non-zero digit, and then followed by a sequence of 0 to 9

    kHexInteger,
    kHexFloat,
    // in TJS2, hex integer should be like this:
    // 0x1234567890abcdefABCDEF
    // start with 0x, and then followed by a sequence of 0 to 9, a to f, A to F

    kIdentifierOrKeyword,
    // in TJS2, identifier should be like this:
    // _abc
    // start with letter, or full-width letter, or _,
    // and then followed by a sequence of letter, or full-width letter, or _, or digit
    // first character cannot be digit
    // in DFA `TjsIsIdentifierDfa`, we will not distinguish identifier and keyword
    // because we can do this in `TjsIsIdentifierDfa`
};

inline bool UnicodeIsInRange(char32_t ch, char32_t lower, char32_t upper) {
    return ch >= lower && ch <= upper;
}
bool IsSpaceChar(char32_t ch);

class TjsLexicalDfa: public AbstractDfa<LexicalDfaState, char32_t> {
  public:
    TjsLexicalDfa():
        AbstractDfa(kStart, kReject) {};
    [[nodiscard]] bool Accept() const override;
    [[nodiscard]] bool Reject() const override;
    [[nodiscard]] LexicalDfaState Transition(LexicalDfaState state, char32_t input) const final;

  private:
    [[nodiscard]] bool MayBeIdentifierOrKeyword(char32_t ch) const;

    const LexicalDfaState kIntermediateStates[1] {
        kNotDecimalOrFloat,
    };  // intermediate_states
    // intermediate states are states that are not final states, but not Reject states.
    [[nodiscard]] bool IsIntermediateState(LexicalDfaState state) const;

    // single character symbols
    const char32_t kSingleCharacterSymbolChar[24] {
        // always make it same to `enum TjsTokenType` in `TjsToken.h`
            '!', '#', '$', '%', '&',
            '*', '+', ',', '-', '.',
            '/', ':', '<', '=', '>',
            '?', ';', '@', '^', '\\',
            '|', '~', '\'', '\"'
    };
    [[nodiscard]] bool IsSingleCharacterSymbol(char32_t input) const;

    // brackets
    const char32_t kBracketChar[6] {
            // always make it same to `enum TjsTokenType` in `TjsToken.h`
            '(', ')', '[', ']', '{', '}'
    };
    [[nodiscard]] bool IsBracket(char32_t input) const;
    static bool IsHexChar(char32_t input);

    [[nodiscard]] LexicalDfaState TransitionHandle_kStart(char32_t input) const;
    [[nodiscard]] static LexicalDfaState TransitionHandle_kNotDecimalOrFloat(
        char32_t input
        );

};

class TjsIsIdentifierDfa: public AbstractDfa<int, char> {

};

class TjsLexicalAnalyzer {
};

} // tjs_analysis

#endif //TJS2JSON_TJS_LEXICAL_ANALYZER_H

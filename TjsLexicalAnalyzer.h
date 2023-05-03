//
// Created by murasame on 23-4-30.
//

#ifndef TJS2JSON_TJS_LEXICAL_ANALYZER_H
#define TJS2JSON_TJS_LEXICAL_ANALYZER_H

#include <utility>
#include <map>
#include <memory>
#include <variant>
#include "AbstractDfa.h"
#include "TjsToken.h"

using std::variant;
using std::unique_ptr;
using std::vector;
using std::u32string;

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
    // in DFA `TjsIsIdentifierOrKeyWord`, we will not distinguish identifier and keyword
    // because we can do this in `TjsIsIdentifierOrKeyWord`

};  // enum LexicalDfaState

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
    void set_state(LexicalDfaState new_state);

  private:
    [[nodiscard]] bool MayBeIdentifierOrKeyword(char32_t ch) const;

    const LexicalDfaState kIntermediateStates[1] {
        kNotDecimalOrFloat,
    };  // intermediate_states
    // intermediate states are states that are not final states, but not Reject states.
    [[nodiscard]] bool IsIntermediateState(LexicalDfaState state) const;

    // single character symbols
    static constexpr char32_t kSingleCharacterSymbolChar[24] {
        // always make it same to `enum TjsTokenType` in `TjsToken.h`
            '!', '#', '$', '%', '&',
            '*', '+', ',', '-', '.',
            '/', ':', '<', '=', '>',
            '?', ';', '@', '^', '\\',
            '|', '~', '\'', '\"'
    };
    [[nodiscard]] bool IsSingleCharacterSymbol(char32_t input) const;

    // brackets
    static constexpr char32_t kBracketChar[6] {
            // always make it same to `enum TjsTokenType` in `TjsToken.h`
            '(', ')', '[', ']', '{', '}'
    };
    [[nodiscard]] bool IsBracket(char32_t input) const;
    static bool IsHexChar(char32_t input);

    [[nodiscard]] LexicalDfaState TransitionHandle_kStart(char32_t input) const;
    [[nodiscard]] static LexicalDfaState TransitionHandle_kNotDecimalOrFloat(
        char32_t input
        );

};  // class TjsLexicalDfa

// map u32string to TjsTokenType
TjdUnknownToken TjsIsIdentifierOrKeyWord(const u32string& input);
const static u32string kTjsKeywords[] = {
        // keep it same to `enum TjsTokenType` in `TjsToken.h`
        U"break", U"case", U"catch", U"class",
        U"continue", U"default", U"delete", U"do",
        U"else", U"extends", U"for", U"function",
        U"getter", U"global",U"if", U"incontextof",
        U"infinity",U"invalidate", U"instanceof", U"int",
        U"isvalid",U"NaN", U"new", U"null",
        U"octet",U"override", U"property", U"real",
        U"return",U"setter", U"string", U"super",
        U"switch",U"this", U"throw", U"try",
        U"typeof",U"var", U"void", U"while",
        U"with",
};
const static u32string kTjsReservedWord[] = {
        // keep it same to `enum TjsTokenType` in `TjsToken.h`
        U"const", U"export", U"enum", U"finally",
        U"import", U"in", U"protected", U"private",
        U"public", U"synchronized", U"static"
};
const static TjsTokenType kTjsKeywordsMapper[] = {
        // keep it same to above
        kBreak, kCase, kCatch, kClass,
        kContinue, kDefault, kDelete, kDo,
        kElse, kExtends, kFor, kFunction,
        kGetter, kGlobal, kIf, KInContextOf,
        kInfinity, kInvalidate, kInstanceOf,
        kInt_, kIsValid,kNaN, kNew, kNull,
        kOctet,kOverride, kProperty, kReal_,
        kReturn,kSetter, kString_, kSuper,
        kSwitch,kThis, kThrow, kTry,
        kTypeOf,kVar, kVoid, kWhile,
        kWith,
};

TjsNoAttributeToken TjsIsSingleCharacterSymbol(const u32string& input);
const static u32string kTjsSymbolString[] = {
        // keep it same to `enum TjsTokenType` in `TjsToken.h`

        // single character symbols
        U"!", U"#", U"$", U"%",
        U"&", U"*", U"+", U",",
        U"-", U".", U"/", U":",
        U"<", U"=", U">", U"?",
        U";", U"@", U"^", U"\\",
        U"|", U"~", U"\'", U"\"",

        // brackets
        U"(", U")", U"[", U"]",
        U"{", U"}",

        // double character symbols
        U"!=", U"%=", U"*=", U"+=",
        U"-=", U"/=", U"\\=", U"^=",
        U"|=", U"&=", U"++", U"--",
        U"<<", U">>", U"<=", U">=",
        U"==", U"&&", U"||", U"%[",

        // triple character symbols
        U"!==", U"===", U"&&=", U"||=",
        U"...", U"<->", U"<<=", U">>=",
        U">>>",

        // longer symbols
        U">>>="
};
const static TjsTokenType kTjsSymbolMapper[] = {
        // keep it same to above

        kPunct, kHashtag, kDollar, kPercent,
        kAmpersand, kAsterisk, kPlus, kComma,
        kMinus, kDot, kSlash, kColon,
        kLess, kEqual, kGreater, kQuestion,
        kSemicolon, kAt, kCaret, kBackslash,
        kVerticalBar, kTilde, kQuote, kDoubleQuote,

        kLeftParen, kRightParen, kLeftBracket, kRightBracket,
        kLeftBrace, kRightBrace,

        kNotEqual, kModAssign, kMulAssign, kAddAssign,
        kSubAssign, kDivAssign, kEvenlyDivAssign, kXorAssign,
        kBitwiseOrAssign, kBitwiseAndAssign, kSelfPlus, kSelfMinus,
        kLeftShift, kRightShift, kLessEqual, kGreaterEqual,
        kEqualEqual, kAnd, kOr, kDictionaryStart,

        kNotStrictEqual, kStrictEqual, kAndAssign, kOrAssign,
        kArguments, kSwap, kLeftShiftAssign, kRightShiftAssign,
        kUnsignedRightShift,

        kUnsignedRightShiftAssign
};

struct TjsLexicalError {
    int row;
    int col;
    std::string message;
};

class TjsLexicalAnalyzer {
  private:
    TjsLexicalDfa dfa_{};
    unsigned int row{1};
    unsigned int col{0};
    unique_ptr<vector<u32string>> code_lines_;
    unique_ptr<vector<TjsLexicalError>> errors;
  public:
    struct RunResult {
        unique_ptr<vector<TjdUnknownToken>> tokens;
        vector<TjsLexicalError> errors;
    };
    explicit TjsLexicalAnalyzer(const u32string& code);
    unique_ptr<RunResult> Run();
};

inline char32_t get_char_in_string (const u32string& str, size_t index);
unique_ptr<vector<u32string>> SplitCodeToLines(const u32string& code);

} // tjs_analysis

#endif //TJS2JSON_TJS_LEXICAL_ANALYZER_H

//
// Created by murasame on 23-4-30.
//

#ifndef TJS2JSON_TJS_TOKEN_H
#define TJS2JSON_TJS_TOKEN_H

#include <string>
#include <cstdint>
#include <utility>

namespace tjs_analysis {

enum TjsTokenType {
    // single character
    kPunct,     // !
    kHashtag,   // #
    kDollar,    // $
    kPercent,   // %
    kAmpersand, // &
    kAsterisk,  // *
    kPlus,      // +
    kComma,     // ,
    kMinus,     // -
    kDot,       // .
    kSlash,     // /
    kColon,     // :
    kLess,      // <
    kEqual,     // =
    kGreater,   // >
    kQuestion,  // ?
    kSemicolon, // ;
    kAt,        // @
    kCaret,     // ^    xor
    kBackslash, // \
    kVerticalBar,   // |
    kTilde,     // ~

    // brackets
    kLeftParen,     // (
    kRightParen,    // )
    kLeftBracket,   // [
    kRightBracket,  // ]
    kLeftBrace,     // {
    kRightBrace,    // }

    // double character
    kNotEqual,      // !=
    kModAssign,     // %=
    kMulAssign,     // *=
    kAddAssign,     // +=
    kSubAssign,     // -=
    kDivAssign,     // /=
    kEvenlyDivAssign,  // \=
    kXorAssign,     // ^=
    kBitwiseOrAssign,   // |=
    kBitwiseAndAssign,  // &=
    kSelfPlus,      // ++
    kSelfMinus,     // --
    kLeftShift,     // <<
    kRightShift,    // >>
    kLessEqual,     // <=
    kGreaterEqual,  // >=
    kEqualEqual,    // ==
    kOr,            // ||
    kAnd,           // &&
    kDictionaryStart,   // %[

    // triple character
    kNotStrictEqual,    // !==
    kStrictEqual,       // ===
    kAndAssign,         // &&=
    kOrAssign,          // ||=
    kArguments,         // ...
    kExchange,          // <->
    kLeftShiftAssign,   // <<=
    kRightShiftAssign,  // >>=
    kUnsignedRightShift,// >>>

    // longer character
    kUnsignedRightShiftAssign,  // >>>=

    // constant
    kVoid,      // void
    kInteger,   // Integer
    kReal,      // Real
    kString,    // String
    kBoolean_,  // Boolean (Deprecated in TJS2)

    // keyword
    kBreak,     // break
    kCase,      // case
    kCatch,     // catch
    kClass,     // class
    kContinue,  // continue
    kDefault,   // default
    kDo,        // do
    kElse,      // else
    kExtends,   // extends
    kFor,       // for
    kFunction,  // function
    kGetter,    // getter()
    kGlobal,    // global
    kIf,        // if
    KInContextOf, // incontextof
    kInvalidate,    // invalidate
    kIsValid,   // isvalid
    kNew,       // new
    kNull,      // null
    kOverride,  // override
    kProperty,  // property
    kReturn,    // return
    kSetter,    // setter()
    kSuper,     // super
    kSwitch,    // switch
    kThis,      // this
    kThrow,     // throw
    kTry,       // try
    kTypeOf,    // typeof
    kVar,       // var
    kWhile,     // while
    kWith,      // with

    // identifier
    kIdentifier,    // ${identifier}

};  // enum TjsTokenType

template <typename T>
class TjsToken {
  private:
    TjsTokenType type_;
  protected:
    T attribute_;
  public:
    TjsToken(TjsTokenType type, T attribute) : type_(type), attribute_(std::move(attribute)) {}
    TjsTokenType getType();
    virtual T getAttribute() = 0;
    static constexpr bool* NO_ATTRIBUTE = nullptr; // for no attribute
};

class TjsNoAttributeToken : public TjsToken<const bool*> {
  public:
    explicit TjsNoAttributeToken(TjsTokenType type) :
                                 TjsToken(type, NO_ATTRIBUTE) {}
  private:
    const bool* getAttribute() final;
};
class TjsIntegerToken : public TjsToken<int64_t> {
  public:
    explicit TjsIntegerToken(int64_t attribute) : TjsToken(kInteger, attribute) {}
    int64_t getAttribute() final;
};
class TjsRealToken : public TjsToken<double> {
  public:
    explicit TjsRealToken(double attribute) : TjsToken(kReal, attribute) {}
    double getAttribute() final;
};
class TjsStringToken : public TjsToken<std::string> {
  public:
    explicit TjsStringToken(std::string attribute) :
                            TjsToken(kString, std::move(attribute)) {}
    std::string getAttribute() final;
};
class TjsBooleanToken : public TjsToken<bool> {
  public:
    explicit TjsBooleanToken(bool attribute) : TjsToken(kBoolean_, attribute) {}
    bool getAttribute() final;
};
class TjsIdentifierToken : public TjsToken<std::string> {
  public:
    explicit TjsIdentifierToken(std::string attribute) :
                            TjsToken(kIdentifier, std::move(attribute)) {}
    std::string getAttribute() final;
};


} // tjs_analysis

#endif //TJS2JSON_TJS_TOKEN_H

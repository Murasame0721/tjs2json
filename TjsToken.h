//
// Created by murasame on 23-4-30.
//

#ifndef TJS2JSON_TJS_TOKEN_H
#define TJS2JSON_TJS_TOKEN_H

#include <variant>
#include <memory>
#include <map>
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
    kBackslash, // '\'
    kVerticalBar,   // |
    kTilde,     // ~
    kQuote,     // '
    kDoubleQuote,   // "

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
    kSwap,          // <->
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
    kDelete,    // delete
    kDo,        // do
    kElse,      // else
    kExtends,   // extends
    kFor,       // for
    kFunction,  // function
    kGetter,    // getter()
    kGlobal,    // global
    kIf,        // if
    KInContextOf, // incontextof
    kInfinity,  // infinity
    kInvalidate,    // invalidate
    kInstanceOf,    // instanceof
    kInt_,      // int() or (int)
    kIsValid,   // isvalid
    kNaN,       // NaN
    kNew,       // new
    kNull,      // null
    kOctet,     // octet
    kOverride,  // override
    kProperty,  // property
    kReal_,     // real() or (real)
    kReturn,    // return
    kSetter,    // setter()
    kString_,   // string() or (string)
    kSuper,     // super
    kSwitch,    // switch
    kThis,      // this
    kThrow,     // throw
    kTry,       // try
    kTypeOf,    // typeof
    kVar,       // var
    // kVoid,      // void (in constant)
    kWhile,     // while
    kWith,      // with

    // reserved word
    kConst,     // const
    kExport,    // export
    kEnum,      // enum
    kFinally,   // finally
    kImport,    // import
    kIn,        // in
    kProtected, // protected
    kPrivate,   // private
    kPublic,    // public
    kSynchronized,  // synchronized
    kStatic,    // static

    // identifier
    kIdentifier,    // ${identifier}

    // blank
    kBlankChar,     // ''

};  // enum TjsTokenType

} // tjs_analysis

#endif //TJS2JSON_TJS_TOKEN_H

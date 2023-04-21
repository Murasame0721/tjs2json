//
// All keywords and symbols in TJS are defined here.
//

#ifndef TJS2JSON_KEYWORD_SYMBOLS_H
#define TJS2JSON_KEYWORD_SYMBOLS_H

namespace lexical_analysis {

/*
 * ==========================================
 * Internal code of Expressions and Operators
 * ==========================================
 * */


    enum Operator {
        monocular_operator,     // enum Monocular_Operator
        conditional_operator,   // enum Conditional_Operator
        logical_operator,       // enum Logical_Operator (Does not include "!")
        binary_operator,        // enum Binary_Operator (Does not include "~", "~" is a monocular operator)
        shift_operator,         // enum Shift_Operator
        assign_operator,        // enum Assign_Operator
        equal_operator,         // enum Equal_Operator
        compare_operator,       // enum Compare_Operator
        math_operator,          // enum Math_Operator
        bracket_operator,       // enum Bracket_Operator
        type_transfer_operator, // enum Type_Transfer_Operator

        INSTANCEOF,             // instanceof
        EVAL,                   // "!" behind of an expression
        BEHIND_IF,              // if (Not "if" in process controlling)
        COMMA,                  // ,
    };

    enum Monocular_Operator {
        SEMICOLON,          // ;
        NOT,                // "!" before of an expression
        BIT_NOT,            // ~
        DECREMENT,          // --
        INCREMENT,          // ++
        IS_VALID,           // isvalid
        DELETE,             // delete
        TYPEOF,             // typeof
        STRING_H1,          // #
        STRING_H2,          // $
        POSITIVE,           // +
        NEGATIVE,           // -
        ADDRESS,            // &
        DEREFERENCE         // *
    };

    enum Conditional_Operator {
        CONDITIONAL,        // ?
        COLON,              // :
    };

    enum Logical_Operator {
        AND,                // &&
        OR,                 // ||
    };

    enum Binary_Operator {
        BIT_AND,            // &
        BIT_OR,             // |
        BIT_XOR,            // ^
    };

    enum Shift_Operator {
        LEFT_SHIFT,         // <<
        RIGHT_SHIFT,        // >>
        RIGHT_SHIFT_ZERO    // >>>
    };

    enum Assign_Operator {
        ASSIGN,             // =
        SWAP,               // <->
        BIT_AND_ASSIGN,     // &=
        BIT_OR_ASSIGN,      // |=
        BIT_XOR_ASSIGN,     // ^=
        ADD_ASSIGN,         // +=
        SUB_ASSIGN,         // -=
        MUL_ASSIGN,         // *=
        DIV_ASSIGN,         // /=
        MOD_ASSIGN,         // %=
        AND_ASSIGN,         // &&=
        OR_ASSIGN,          // ||=
        LEFT_SHIFT_ASSIGN,  // <<=
        RIGHT_SHIFT_ASSIGN, // >>=
        RIGHT_SHIFT_ZERO_ASSIGN, // >>>=
    };

    enum Equal_Operator {
        EQUAL,              // ==
        NOT_EQUAL,          // !=
        STRICT_EQUAL,       // ===
        STRICT_NOT_EQUAL    // !==
    };

    enum Compare_Operator {
        LESS,               // <
        LESS_EQUAL,         // <=
        GREATER,            // >
        GREATER_EQUAL       // >=
    };

    enum Math_Operator {
        ADD,                // +
        SUB,                // -
        MUL,                // *
        DIV,                // /
        MOD                 // %
    };

    enum Bracket_Operator {
        LEFT_BRACKET,       // (
        RIGHT_BRACKET,      // )
        LEFT_SQUARE_BRACKET,// [
        RIGHT_SQUARE_BRACKET,// ]
        LEFT_CURLY_BRACKET, // {
        RIGHT_CURLY_BRACKET // }
    };

    enum Type_Transfer_Operator {
        FORCE_INT,          // int
        FORCE_REAL,         // real
        FORCE_STRING,       // string
    };


/*
 * ==========================================
 * Internal code of Keywords
 * ==========================================
 * */

    enum Process_Control_Keyword {
        IF,                 // if
        ELSE,               // else
        SWITCH,             // switch
        CASE,               // case
        DEFAULT,            // default
        WHILE,              // while
        DO,                 // do
        FOR,                // for
        BREAK,              // break
        CONTINUE,           // continue
        RETURN,             // return
    };

    enum Object_Oriented_Keyword {
        NEW_OBJECT,         // new
        INVALID_OBJ,        // invalidate
        PROPERTY,           // property
        WITH,               // with
        CLASS,              // class
        EXTENDS,            // extends
        SUPER,              // super
        THIS,               // this
    };

    enum Variable_Keyword {
        VAR,                // var
        FUNCTION,           // function
        GLOBAL,             // global
        DICTIONARY_STARTER, // "%" in "%[]"
        VOID,               // void
        NULL_KEYWORD,       // null
        ARROW,              // =>
    };


/*
 * ==========================================
 * Internal code of Constants
 * ==========================================
 * */

    enum Constant {
        TRUE,               // true
        FALSE,              // false
        NAN,                // NaN
        INFINITY,           // Infinity
        NEGATIVE_INFINITY,  // -Infinity
    };
}
#endif //TJS2JSON_KEYWORD_SYMBOLS_H

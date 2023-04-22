//
// Declare the class of tokens
//

#ifndef TJS2JSON_LEXICAL_TOKENS_H
#define TJS2JSON_LEXICAL_TOKENS_H

#include "Keyword_Symbols.h"
#include <stdexcept>
#include <string>


namespace lexical_analysis {













/*
 * =======================================
 * Token Classes
 * =======================================
 * */

    template<typename TJS_Token_Name, typename TJS_Attribution>
    class TJS_Token {
        //Abstract class of all kinds of tokens
    protected:
        TJS_Token_Name name;
        TJS_Attribution attribution{};
    public:
        virtual TJS_Token_Name get_name() = 0;
        virtual TJS_Attribution get_attribution() = 0;
        TJS_Token(TJS_Token_Name name, TJS_Attribution attribution) : name(name), attribution(attribution) {}
    };


/*
 * ----------------
 * Operator Token
 * ----------------
 * */

// Abstract class of all kinds of operator tokens
    template<typename TJS_Token_Name>
    class TJS_Operator_Token : public TJS_Token<TJS_Token_Name, bool> {
    protected:
        Operator operator_type;
    public:
        Operator get_operator_type() {
            return this->operator_type;
        }
        bool get_attribution() override {
            throw std::runtime_error("Operator token has no attribution");
        }
        TJS_Token_Name get_name() override { return this->name; }
        TJS_Operator_Token(TJS_Token_Name _name, Operator _operator_type) :
                TJS_Token<TJS_Token_Name, bool>(_name, false), operator_type(_operator_type) {}
    };


    class TJS_Special_Token : public TJS_Operator_Token<Operator> {
        // Special operator token, including "instanceof", "eval", "if", ",", ";"
    public:
        TJS_Special_Token(Operator _name) : TJS_Operator_Token<Operator>(_name, _name) {
            //examine if _name is a special operator
            if ( _name != INSTANCEOF &&
                _name != EVAL &&
                _name != BEHIND_IF &&
                _name != COMMA &&
                _name != SEMICOLON)
            {
                throw std::runtime_error("Special token must be INSTANCEOF, EVAL, BEHIND_IF, COMMA or SEMICOLON");
            }
        }
    };

    class TJS_Mono_Operator_Token : public TJS_Operator_Token<Monocular_Operator> {
    public:
        TJS_Mono_Operator_Token(Monocular_Operator _name) : TJS_Operator_Token<Monocular_Operator>(_name,monocular_operator) {}
    };

    class TJS_Conditional_Operator_Token : public TJS_Operator_Token<Conditional_Operator> {
    public:
        TJS_Conditional_Operator_Token(Conditional_Operator _name) : TJS_Operator_Token<Conditional_Operator>(_name,conditional_operator) {}
    };

    class TJS_Logical_Operator_Token : public TJS_Operator_Token<Logical_Operator> {
    public:
        TJS_Logical_Operator_Token(Logical_Operator _name) : TJS_Operator_Token<Logical_Operator>(_name,logical_operator) {}
    };

    class TJS_Binary_Operator_Token : public TJS_Operator_Token<Binary_Operator> {
    public:
        TJS_Binary_Operator_Token(Binary_Operator _name) : TJS_Operator_Token<Binary_Operator>(_name,binary_operator) {}
    };

    class TJS_Shift_Operator_Token : public TJS_Operator_Token<Shift_Operator> {
    public:
        TJS_Shift_Operator_Token(Shift_Operator _name) : TJS_Operator_Token<Shift_Operator>(_name,shift_operator) {}
    };

    class TJS_Assign_Operator_Token : public TJS_Operator_Token<Assign_Operator> {
    public:
        TJS_Assign_Operator_Token(Assign_Operator _name) : TJS_Operator_Token<Assign_Operator>(_name,assign_operator) {}
    };

    class TJS_Equal_Operator_Token : public TJS_Operator_Token<Equal_Operator> {
    public:
        TJS_Equal_Operator_Token(Equal_Operator _name) : TJS_Operator_Token<Equal_Operator>(_name,equal_operator) {}
    };

    class TJS_Compare_Operator_Token : public TJS_Operator_Token<Compare_Operator> {
    public:
        TJS_Compare_Operator_Token(Compare_Operator _name) : TJS_Operator_Token<Compare_Operator>(_name,compare_operator) {}
    };

    class TJS_Math_Operator_Token : public TJS_Operator_Token<Math_Operator> {
    public:
        TJS_Math_Operator_Token(Math_Operator _name) : TJS_Operator_Token<Math_Operator>(_name,math_operator) {}
    };

    class TJS_Bracket_Operator_Token : public TJS_Operator_Token<Bracket_Operator> {
    public:
        TJS_Bracket_Operator_Token(Bracket_Operator _name) : TJS_Operator_Token<Bracket_Operator>(_name,bracket_operator) {}
    };

    class TJS_Type_Transfer_Operator_Token : public TJS_Operator_Token<Type_Transfer_Operator> {
    public:
        TJS_Type_Transfer_Operator_Token(Type_Transfer_Operator _name) : TJS_Operator_Token<Type_Transfer_Operator>(_name,type_transfer_operator) {}
    };



/*
 * ----------------
 * Keyword Token
 * ----------------
 * */

    template<typename TJS_Keyword_Type>
    class TJS_Keyword_Token : public TJS_Token<TJS_Keyword_Type, bool> {
        //Abstract class of all kinds of keyword tokens
    public:
        explicit TJS_Keyword_Token(TJS_Keyword_Type _name) : TJS_Token<TJS_Keyword_Type, bool>(_name, false) {}
        TJS_Keyword_Type get_name() override { return this->name; }
        bool get_attribution() override {
            throw std::runtime_error("Process control keyword token has no attribution");
        }
    };

    class TJS_Process_Control_Keyword_Token : public TJS_Keyword_Token<Process_Control_Keyword> {
    public:
        TJS_Process_Control_Keyword_Token(Process_Control_Keyword _name) : TJS_Keyword_Token<Process_Control_Keyword>(_name) {}
    };

    class TJS_Object_Oriented_Keyword_Token : public TJS_Keyword_Token<Object_Oriented_Keyword> {
    public:
        TJS_Object_Oriented_Keyword_Token(Object_Oriented_Keyword _name) : TJS_Keyword_Token<Object_Oriented_Keyword>(_name) {}
    };

    class TJS_Variable_Keyword_Token : public TJS_Keyword_Token<Variable_Keyword> {
    public:
        TJS_Variable_Keyword_Token(Variable_Keyword _name) : TJS_Keyword_Token<Variable_Keyword>(_name) {}
    };

/*
 * ----------------
 * Constant Token
 * ----------------
 * */

    //TODO: add constant types

}






#endif //TJS2JSON_LEXICAL_TOKENS_H

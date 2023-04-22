/* Basic data types of TJS
 *
 * include:
 * 1. void
 * 2. boolean
 * 3. integer
 * 4. real
 * 5. string
 * 6. octet
 * */

#ifndef TJS2JSON_TJS_DATA_TYPES_H
#define TJS2JSON_TJS_DATA_TYPES_H

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace TJS_Data_Types{

    using namespace std;

    enum special_number{
        NaN,
        Infinity,
        Negative_Infinity,
        not_special
    };
    struct expanding_integer{
        int64_t int64;
        special_number special_number;
    };
    struct expanding_float{
        double double_;
        special_number special_number;
    };








    template<typename Internal_Data_Type>
    class TJS_Data{
        // Abstract class of all kinds of data
    protected:
        Internal_Data_Type data;
    public:
        explicit TJS_Data(Internal_Data_Type data) : data(std::move(data)) {}
        Internal_Data_Type get_data() {
            return this->data;
        }

        // monocular operator
        virtual string $typeof() = 0;
    };








    class TJS_Void : public TJS_Data<bool>{
        TJS_Void() : TJS_Data(false) {}
    public:
        string $typeof() final { return "void"; }
    };

    class TJS_Boolean : public TJS_Data<bool>{
    public:
        explicit TJS_Boolean(bool data) : TJS_Data(data) {}
        string $typeof() final { return "Boolean"; }
    };


    class TJS_Integer : public TJS_Data<expanding_integer>{
    public:
        explicit TJS_Integer(expanding_integer data) : TJS_Data(data) {}
        string $typeof() final { return "Integer"; }
    };

    class TJS_Real : public TJS_Data<expanding_float>{
    public:
        explicit TJS_Real(expanding_float data) : TJS_Data(data) {}
        string $typeof() final { return "Real"; }
    };

    class TJS_String : public TJS_Data<string>{
    public:
        explicit TJS_String(string data) : TJS_Data(std::move(data)) {}
        string $typeof() final { return "String"; }
    };

    class TJS_Octet : public TJS_Data<vector<uint8_t>>{
    public:
        explicit TJS_Octet(vector<uint8_t> data) : TJS_Data(std::move(data)) {}
        string $typeof() final { return "Octet"; }
    };






    /*
     * -----------------
     * convert_to_xxx
     * -----------------
     * */

    // convert to boolean
    shared_ptr<TJS_Boolean> convert_to_boolean(shared_ptr<TJS_Boolean> _data);
    shared_ptr<TJS_Boolean> convert_to_boolean(const shared_ptr<TJS_Integer>& _data);
    shared_ptr<TJS_Boolean> convert_to_boolean(const shared_ptr<TJS_Real>& _data);
    shared_ptr<TJS_Boolean> convert_to_boolean(const shared_ptr<TJS_String>& _data);


    // convert to integer
    shared_ptr<TJS_Integer> convert_to_integer(const shared_ptr<TJS_Boolean>& _data);
    shared_ptr<TJS_Integer> convert_to_integer(shared_ptr<TJS_Integer> _data);
    shared_ptr<TJS_Integer> convert_to_integer(const shared_ptr<TJS_Real>& _data);
    shared_ptr<TJS_Integer> convert_to_integer(const shared_ptr<TJS_String>& _data);


    // convert to real
    shared_ptr<TJS_Real> convert_to_real(const shared_ptr<TJS_Boolean>& _data);
    shared_ptr<TJS_Real> convert_to_real(const shared_ptr<TJS_Integer>& _data);
    shared_ptr<TJS_Real> convert_to_real(shared_ptr<TJS_Real> _data);
    shared_ptr<TJS_Real> convert_to_real(const shared_ptr<TJS_String>& _data);


    // convert to string
    shared_ptr<TJS_String> convert_to_string(const shared_ptr<TJS_Boolean>& _data);
    shared_ptr<TJS_String> convert_to_string(const shared_ptr<TJS_Integer>& _data);
    shared_ptr<TJS_String> convert_to_string(const shared_ptr<TJS_Real>& _data);
    shared_ptr<TJS_String> convert_to_string(shared_ptr<TJS_String> _data);




    /*
     * -----------------
     * add
     * -----------------
     * */


    // void + void = void
    shared_ptr<TJS_Void> TJS_add(const shared_ptr<TJS_Void>& _data1, const shared_ptr<TJS_Void>& _data2);

    // void + boolean = NaN
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Void>& _data1, const shared_ptr<TJS_Boolean>& _data2);
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Boolean>& _data1, const shared_ptr<TJS_Void>& _data2);

    // void + integer = NaN
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Void>& _data1, const shared_ptr<TJS_Integer>& _data2);
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Void>& _data2);

    // void + real = NaN
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Void>& _data1, const shared_ptr<TJS_Real>& _data2);
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Real>& _data1, const shared_ptr<TJS_Void>& _data2);

    // void + string = "void" + string
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_Void>& _data1, const shared_ptr<TJS_String>& _data2);
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_String>& _data1, const shared_ptr<TJS_Void>& _data2);

    // boolean + boolean = number + number
    shared_ptr<TJS_Integer> TJS_add(const shared_ptr<TJS_Boolean>& _data1, const shared_ptr<TJS_Boolean>& _data2);

    // boolean + integer = number + number
    shared_ptr<TJS_Integer> TJS_add(const shared_ptr<TJS_Boolean>& _data1, const shared_ptr<TJS_Integer>& _data2);
    shared_ptr<TJS_Integer> TJS_add(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Boolean>& _data2);

    // boolean + real = number + number
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Boolean>& _data1, const shared_ptr<TJS_Real>& _data2);
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Real>& _data1, const shared_ptr<TJS_Boolean>& _data2);

    // boolean + string = string + string
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_Boolean>& _data1, const shared_ptr<TJS_String>& _data2);
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_String>& _data1, const shared_ptr<TJS_Boolean>& _data2);

    // integer + integer = integer
    shared_ptr<TJS_Integer> TJS_add(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Integer>& _data2);

    // integer + real = real
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Real>& _data2);
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Real>& _data1, const shared_ptr<TJS_Integer>& _data2);

    // integer + string = string + string
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_String>& _data2);
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_String>& _data1, const shared_ptr<TJS_Integer>& _data2);

    // real + real = real
    shared_ptr<TJS_Real> TJS_add(const shared_ptr<TJS_Real>& _data1, const shared_ptr<TJS_Real>& _data2);

    // real + string = string + string
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_Real>& _data1, const shared_ptr<TJS_String>& _data2);
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_String>& _data1, const shared_ptr<TJS_Real>& _data2);

    // string + string = string
    shared_ptr<TJS_String> TJS_add(const shared_ptr<TJS_String>& _data1, const shared_ptr<TJS_String>& _data2);


    /*
     * -----------------
     * other operators
     * -----------------
     * */

    // integer - integer = integer
    // other - other = real - real
    template <typename T1, typename T2>
    shared_ptr<TJS_Real> TJS_sub(const shared_ptr<T1>& _data1, const shared_ptr<T2>& _data2);
    shared_ptr<TJS_Integer> TJS_sub(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Integer>& _data2);


    // integer * integer = integer
    // other * other = real * real
    template <typename T1, typename T2>
    shared_ptr<TJS_Real> TJS_mul(const shared_ptr<T1>& _data1, const shared_ptr<T2>& _data2);
    shared_ptr<TJS_Integer> TJS_mul(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Integer>& _data2);


    // integer / integer = integer
    // other / other = real / real
    template <typename T1, typename T2>
    shared_ptr<TJS_Real> TJS_div(const shared_ptr<T1>& _data1, const shared_ptr<T2>& _data2);
    shared_ptr<TJS_Integer> TJS_div(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Integer>& _data2);


    // integer % integer = integer
    // other % other = real % real
    template <typename T1, typename T2>
    shared_ptr<TJS_Real> TJS_mod(const shared_ptr<T1>& _data1, const shared_ptr<T2>& _data2);
    shared_ptr<TJS_Integer> TJS_mod(const shared_ptr<TJS_Integer>& _data1, const shared_ptr<TJS_Integer>& _data2);


    /*
     * -----------------
     * monoculture operators
     * -----------------
     * */

    // not (any) = boolean
    template <typename T>
    shared_ptr<TJS_Boolean> TJS_not(const shared_ptr<T>& _data);

    // # (any) = string
    template <typename T>
    shared_ptr<TJS_String> TJS_hash(const shared_ptr<T>& _data);

    // $ (any) = $ (Integer) = string
    template <typename T>
    shared_ptr<TJS_String> TJS_dollar(const shared_ptr<T>& _data);


    /*
     * -----------------
     * compare
     * -----------------
     * */

    //TODO： equal and strict equal


    struct compare_result{
        bool greater;
        bool greater_or_equal;
        bool less;
        bool less_or_equal;
    };
}

#endif //TJS2JSON_TJS_DATA_TYPES_H

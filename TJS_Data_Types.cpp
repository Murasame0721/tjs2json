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

#include "TJS_Data_Types.h"
#include <charconv>

namespace TJS_Data_Types{
    using namespace std;


    /*
    * -----------------
    * convert_to_xxx
    * -----------------
    * */

    // convert to boolean
    shared_ptr<TJS_Boolean> convert_to_boolean(shared_ptr<TJS_Boolean> _data) { return _data; }
    shared_ptr<TJS_Boolean> convert_to_boolean(const shared_ptr<TJS_Integer>& _data)
    {
        if (_data->get_data().int64 != 0 && _data->get_data().special_number == NaN)
            return make_shared<TJS_Boolean>(true);
        else
            return make_shared<TJS_Boolean>(false);
    }
    shared_ptr<TJS_Boolean> convert_to_boolean(const shared_ptr<TJS_Real>& _data)
    {
        if (_data->get_data().double_ != 0 && _data->get_data().special_number == NaN)
            return make_shared<TJS_Boolean>(true);
        else
            return make_shared<TJS_Boolean>(false);
    }
    shared_ptr<TJS_Boolean> convert_to_boolean(const shared_ptr<TJS_String>& _data)
    {
        if (_data->get_data().empty())
            return make_shared<TJS_Boolean>(false);
        else
            return make_shared<TJS_Boolean>(true);
    }


    // convert to integer
    shared_ptr<TJS_Integer> convert_to_integer(const shared_ptr<TJS_Boolean>& _data)
    {
        expanding_integer temp{};
        temp.int64 = _data->get_data();
        temp.special_number = not_special;
        return make_shared<TJS_Integer>(temp);
    }
    shared_ptr<TJS_Integer> convert_to_integer(shared_ptr<TJS_Integer> _data) { return _data; }
    shared_ptr<TJS_Integer> convert_to_integer(const shared_ptr<TJS_Real>& _data)
    {
        expanding_integer temp{};
        temp.int64 = _data->get_data().double_;  // narrow conversion
        temp.special_number = _data->get_data().special_number;
        return make_shared<TJS_Integer>(temp);
    }
    shared_ptr<TJS_Integer> convert_to_integer(const shared_ptr<TJS_String>& _data)
    {
        expanding_integer temp{};
        auto str = _data->get_data();
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), temp.int64);
        temp.special_number = not_special;
        if (ec == std::errc::invalid_argument) {
            temp.special_number = NaN;
        } else if (ec == std::errc::result_out_of_range) {
            temp.special_number = Infinity;
        }
        return make_shared<TJS_Integer>(temp);
    }

    //TODO: complete add, other operators, monoculture operators, compare


}
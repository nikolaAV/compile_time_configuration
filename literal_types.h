#pragma once

#include "char_traits.h"
#include <cstdlib>

// clang-format off

namespace literal
{

template <char... chars>
struct char_sequence : std::integer_sequence<char, chars...> { 
    static const char* value() {
        static constexpr char str[sizeof...(chars) + 1] = { chars..., '\0' };
        return str;
    }
};

template <char... chars>
struct digit_sequence : char_sequence<chars...> { 
    static_assert(char_traits::is_digits<chars...>::value,"char is not a digit");
    static long value() {
        char* end{};
        return std::strtol(char_sequence<chars...>::value(), &end, 10);
    }
};

template <char... chars>
struct xdigit_sequence : char_sequence<chars...> { 
    static_assert(char_traits::is_xdigits<chars...>::value,"char is not a xdigit");
    static long value() {
        char* end{};
        return std::strtol(char_sequence<chars...>::value(), &end, 16);
    }
};

template <char... chars>
struct fdigit_sequence : char_sequence<chars...> { 
    static_assert(char_traits::is_floating_point_digits<chars...>::value,"char is not a floating-point digit sign");
    static double value() {
        char* end{};
        return std::strtod(char_sequence<chars...>::value(), &end);
    }
};

}   // namespace literal

/**
    String literals as non-type template parameters
    To be implemented it uses Gcc extension. 
    @see https://github.com/nikolaAV/skeleton/tree/master/literal_string_type
*/

template <typename T, T... chars>
constexpr literal::char_sequence<chars...> operator""_cs() { return { }; }

template <typename T, T... chars>
constexpr literal::digit_sequence<chars...> operator""_ds() { return { }; }

template <typename T, T... chars>
constexpr literal::xdigit_sequence<chars...> operator""_xs() { return { }; }

template <typename T, T... chars>
constexpr literal::fdigit_sequence<chars...> operator""_fs() { return { }; }


#define SL(s) decltype("" s ""_cs)
#define DL(s) decltype("" s ""_ds)
#define XL(s) decltype("" s ""_xs)
#define FL(s) decltype("" s ""_fs)

// clang-format on

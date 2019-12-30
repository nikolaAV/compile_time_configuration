#pragma once

#include "typelist.hpp"
#include "literal_types.h"

// clang-format off

namespace tag
{
    template <typename T>
    struct name : tl::list<T> {};

    template <typename T>
    struct is_name : std::false_type {};

    template <typename T>
    struct is_name<name<T>> : std::true_type {};
///
    template <typename T>
    struct lib : tl::list<T> {};

    template <typename T>
    struct is_lib : std::false_type {};

    template <typename T>
    struct is_lib<lib<T>> : std::true_type {};
///
    template <typename... Ts>
    struct inputs : tl::list<Ts...> {};

    template <typename T>
    struct is_inputs : std::false_type {};

    template <typename... Ts>
    struct is_inputs<inputs<Ts...>> : std::true_type {};
///
    template <typename... Ts>
    struct outputs : tl::list<Ts...> {};

    template <typename T>
    struct is_outputs : std::false_type {};

    template <typename... Ts>
    struct is_outputs<outputs<Ts...>> : std::true_type {};
///
    template <typename Inputs, typename Outputs>
    struct communication : tl::list<Inputs,Outputs> {
        static_assert(is_inputs<Inputs>::value, "parameter 'Inputs' is invalid");
        static_assert(is_outputs<Outputs>::value, "parameter 'Outputs' is invalid");
    };

    template <typename T>
    struct is_communication : std::false_type {};

    template <typename... Ts>
    struct is_communication<communication<Ts...>> : std::true_type {};

///
    template <typename Name, typename Lib, typename Communication>
    struct node : tl::list<Name,Lib,Communication> {
        static_assert(is_name<Name>::value, "parameter 'Name' is invalid");
        static_assert(is_lib<Lib>::value, "parameter 'Lib' is invalid");
        static_assert(is_communication<Communication>::value, "parameter 'Communication' is invalid");
    };

}   // tag namespace

// clang-format on

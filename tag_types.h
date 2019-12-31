#pragma once

#include "typelist.hpp"
#include "literal_types.h"

// clang-format off

namespace tag
{
    template <typename T>
    struct width : tl::list<T> {};

    template <typename T>
    struct height : tl::list<T> {};

    template <typename T>
    struct min : tl::list<T> {};

    template <typename T>
    struct max : tl::list<T> {};

    template <typename T>
    struct mat_div_factor : tl::list<T> {};

    template <typename T>
    struct mirror_angle_min : tl::list<T> {};

    template <typename T>
    struct mirror_angle_max : tl::list<T> {};

    template <typename T, typename U, typename H>
    struct mirror_pos : tl::list<T,U,H> {};

    template <typename T, typename U>
    struct mirror_angles : tl::list<T,U> {};

    template <typename T>
    struct scene : tl::list<T> {};

    template <typename T>
    struct name : tl::list<T> {
        using list_type = tl::list<T>;
    };

    template <typename T>
    struct lib : tl::list<T> {};

    template <typename... Ts>
    struct inputs : tl::list<Ts...> {};

    template <typename... Ts>
    struct outputs : tl::list<Ts...> {};

    template <typename Inputs, typename Outputs> 
    struct communication;

    template <typename... Ts, typename... Us>
    struct communication<inputs<Ts...>,outputs<Us...>> : tl::list<inputs<Ts...>,outputs<Us...>> {
    };

    template <typename T, typename U, typename H, typename G>
    struct zone;

    template <typename T, typename U, typename H, typename G, typename M, typename P>
    struct zone<name<T>,width<U>,height<H>,mirror_pos<G,M,P>> : tl::list<name<T>,width<U>,height<H>,mirror_pos<G,M,P>> {
    };

    template <typename T, typename U, typename H, typename G>
    struct static_zone : zone<T,U,H,G> {
    };

    template <typename T, typename U, typename H, typename G>
    struct ar_zone : zone<T,U,H,G> {
    };

    template <typename... Ts>
    struct config : tl::list<Ts...>{
    };

    template <typename Name, typename Lib, typename Config, typename Communication>
    struct node;

    template <typename T, typename U, typename I, typename O, typename... Hs>
    struct node<name<T>,lib<U>,config<Hs...>,communication<I,O>> : tl::list<name<T>,lib<U>,config<Hs...>,communication<I,O>> {
        using list_type = tl::list<name<T>,lib<U>,config<Hs...>,communication<I,O>>;
    }; 

}   // tag namespace

// clang-format on

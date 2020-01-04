#pragma once

#include "typelist.hpp"
#include "literal_types.h"

// clang-format off

namespace tag
{
    template <typename T>
    struct width : T {
        static_assert(literal::is_digit_sequence<T>::value,"[tag::width] T is not integer");
    };

    template <typename T>
    struct height : T {
        static_assert(literal::is_digit_sequence<T>::value,"[tag::height] T is not integer");
    };

    template <typename T>
    struct min  : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::min] T is not double");
    };

    template <typename T>
    struct max  : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::max] T is not double");
    };

    template <typename T>
    struct node : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::node] T is not string");
    };

    template <typename T>
    struct ar : T {
        static_assert(literal::is_bdigit_sequence<T>::value,"[tag::ar] T is not boolean type");
    };

    template <typename T>
    struct mat_div_factor : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::mat_div_factor] T is not double");
    };

    template <typename T>
    struct is_mat_div_factor : std::false_type {  
    };

    template <typename T>
    struct is_mat_div_factor<mat_div_factor<T>> : std::true_type {  
    };

    template <typename T>
    struct mirror_angle_min : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::mirror_angle_min] T is not double");
    };

    template <typename T>
    struct is_mirror_angle_min : std::false_type {  
    };

    template <typename T>
    struct is_mirror_angle_min<mirror_angle_min<T>> : std::true_type {  
    };

    template <typename T>
    struct mirror_angle_max : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::mirror_angle_max] T is not double");
    };

    template <typename T>
    struct is_mirror_angle_max : std::false_type {  
    };

    template <typename T>
    struct is_mirror_angle_max<mirror_angle_max<T>> : std::true_type {  
    };

    template <typename T, typename U, typename H>
    struct mirror_pos {
        using low_type = T;
        using mid_type = U;
        using high_type = H;

        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::mirror_pos] 'low' is not double");
        static_assert(literal::is_fdigit_sequence<U>::value,"[tag::mirror_pos] 'mid' is not double");
        static_assert(literal::is_fdigit_sequence<H>::value,"[tag::mirror_pos] 'high' is not double");
    };

    template <typename T, typename U>
    struct mirror_angles;
    
    template <typename T, typename U>
    struct mirror_angles<min<T>,max<U>>
    {
        using min_type = min<T>;
        using max_type = max<U>;
    };

    template <typename T>
    struct scene : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::scene] T is not string");
    };

    template <typename T, typename U, typename H>
    struct nshe; // nodes_show_hide_element
    
    template <typename T, typename U, typename H>
    struct nshe<scene<T>, node<U>, ar<H>> {
        using scene_type = scene<T>;
        using node_type = node<U>;
        using ar_type = ar<H>;
    };

    template <typename... Nshes>
    struct nodes_show_hide {
        using type = tl::list<Nshes...>;
    };
    template <typename T>
    struct name : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::name] T is not string");
    };

    template <typename T>
    struct lib : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::lib] T is not string");
    };

    template <typename... Ts>
    struct inputs {
        using type = tl::list<Ts...>;
    };

    template <typename... Ts>
    struct outputs {
        using type = tl::list<Ts...>;
    };

    template <typename Inputs, typename Outputs> 
    struct communication;

    template <typename... Ts, typename... Us>
    struct communication<inputs<Ts...>,outputs<Us...>> {
        using inputs_type = inputs<Ts...>;
        using outputs_type = outputs<Us...>;
    };


    template <typename T, typename U, typename H, typename G>
    struct zone;

    template <typename T, typename U, typename H, typename G, typename M, typename P>
    struct zone<name<T>,width<U>,height<H>,mirror_pos<G,M,P>> {
        using name_type = name<T>;
        using width_type = width<U>;
        using height_type = height<H>;
        using mirror_pos_type = mirror_pos<G,M,P>;
    };

    template <typename T, typename U, typename H, typename G>
    struct static_zone : zone<T,U,H,G> {
    };

    template <typename T>
    struct is_static_zone : std::false_type {  
    };

    template <typename T, typename U, typename H, typename G>
    struct is_static_zone<static_zone<T,U,H,G>> : std::true_type {  
    };

    template <typename T, typename U, typename H, typename G>
    struct ar_zone : zone<T,U,H,G> {
    };

    template <typename T>
    struct is_ar_zone : std::false_type {  
    };

    template <typename T, typename U, typename H, typename G>
    struct is_ar_zone<ar_zone<T,U,H,G>> : std::true_type {  
    };

    template <typename... Ts>
    struct config {
        using type = tl::list<Ts...>;
    };

    template <typename Config, template <typename> class Condition>
    struct get;

    template <template <typename> class Condition, typename... Ts>
    struct get<config<Ts...>,Condition> {
        using type = tl::front_t<tl::find_if_t<typename config<Ts...>::type, Condition>>;
    };

    template <typename TList, template <typename> class Condition>
    using get_t = typename get<TList,Condition>::type;

    template <typename Name, typename Lib, typename Config, typename Communication>
    struct anode;

    template <typename T, typename U, typename I, typename O, typename... Hs>
    struct anode<name<T>,lib<U>,config<Hs...>,communication<I,O>> {
        using name_type = name<T>;
        using lib_type = lib<U>;
        using config_type = config<Hs...>;
        using communication_type = communication<I,O>;
    }; 


}   // tag namespace

// clang-format on

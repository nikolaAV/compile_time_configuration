#pragma once

#include "typelist.hpp"
#include "literal_types.h"

// clang-format off

namespace tag
{
    template <typename T>
    struct width {
        using type = T;
    };

    template <typename T>
    struct height {
        using type = T;
    };

    template <typename T>
    struct min  {
        using type = T;
    };

    template <typename T>
    struct max {
        using type = T;
    };

    template <typename T>
    struct node {
        using type = T;
    };

    template <typename T>
    struct ar {
        using type = T;
    };

    template <typename T>
    struct mat_div_factor {
        using type = T;
    };

    template <typename T>
    struct is_mat_div_factor : std::false_type {  
    };

    template <typename T>
    struct is_mat_div_factor<mat_div_factor<T>> : std::true_type {  
    };

    template <typename T>
    struct mirror_angle_min {
        using type = T;
    };

    template <typename T>
    struct is_mirror_angle_min : std::false_type {  
    };

    template <typename T>
    struct is_mirror_angle_min<mirror_angle_min<T>> : std::true_type {  
    };

    template <typename T>
    struct mirror_angle_max {
        using type = T;
    };

    template <typename T>
    struct is_mirror_angle_max : std::false_type {  
    };

    template <typename T>
    struct is_mirror_angle_max<mirror_angle_max<T>> : std::true_type {  
    };

    template <typename T, typename U, typename H>
    struct mirror_pos {
        using _1_type = T;
        using _2_type = U;
        using _3_type = H;
    };

    template <typename T, typename U>
    struct mirror_angles {
        using min_type = T;
        using max_type = U;
    };

    template <typename T>
    struct scene {
        using type = T;
    };

    template <typename T, typename U, typename H>
    struct nshe; // nodes_show_hide_element
    
    template <typename T, typename U, typename H>
    struct nshe<scene<T>, node<U>, ar<H>> {
        using scene_type = T;
        using node_type = U;
        using ar_type = H;
    };

    template <typename... Nshes>
    struct nodes_show_hide {
        using type = tl::list<Nshes...>;
    };

    template <typename T>
    struct name {
        using type = T;
    };

    template <typename T>
    struct lib {
        using type = T;
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
        using inputs_type = typename inputs<Ts...>::type;
        using outputs_type = typename outputs<Us...>::type;
    };


    template <typename T, typename U, typename H, typename G>
    struct zone;

    template <typename T, typename U, typename H, typename G, typename M, typename P>
    struct zone<name<T>,width<U>,height<H>,mirror_pos<G,M,P>> {
        using name_type = T;
        using width_type = U;
        using height_type = H;
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

    template <typename TList, template <typename> class Condition>
    using get_tt = typename get_t<TList,Condition>::type;

    template <typename Name, typename Lib, typename Config, typename Communication>
    struct anode;

    template <typename T, typename U, typename I, typename O, typename... Hs>
    struct anode<name<T>,lib<U>,config<Hs...>,communication<I,O>> {
        using name_type = T;
        using lib_type = U;
        using config_type = config<Hs...>;
        using communication_type = communication<I,O>;
    }; 


}   // tag namespace

// clang-format on

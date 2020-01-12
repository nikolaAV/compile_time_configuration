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
    struct is_width : std::false_type {  
    };

    template <typename T>
    struct is_width<width<T>> : std::true_type {  
    };

    template <typename T>
    struct height : T {
        static_assert(literal::is_digit_sequence<T>::value,"[tag::height] T is not integer");
    };

    template <typename T>
    struct is_height : std::false_type {  
    };

    template <typename T>
    struct is_height<height<T>> : std::true_type {  
    };

    template <typename T>
    struct min  : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::min] T is not double");
    };

    template <typename T>
    struct is_min : std::false_type {  
    };

    template <typename T>
    struct is_min<min<T>> : std::true_type {  
    };

    template <typename T>
    struct max  : T {
        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::max] T is not double");
    };

    template <typename T>
    struct is_max : std::false_type {  
    };

    template <typename T>
    struct is_max<max<T>> : std::true_type {  
    };

    template <typename T>
    struct node : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::node] T is not string");
    };

    template <typename T>
    struct is_node : std::false_type {  
    };

    template <typename T>
    struct is_node<node<T>> : std::true_type {  
    };

    template <typename T>
    struct ar : T {
        static_assert(literal::is_bdigit_sequence<T>::value,"[tag::ar] T is not boolean type");
    };

    template <typename T>
    struct is_ar : std::false_type {  
    };

    template <typename T>
    struct is_ar<ar<T>> : std::true_type {  
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

        static_assert(literal::is_fdigit_sequence<T>::value,"[tag::mirror_pos] T ('low') is not double");
        static_assert(literal::is_fdigit_sequence<U>::value,"[tag::mirror_pos] U ('mid') is not double");
        static_assert(literal::is_fdigit_sequence<H>::value,"[tag::mirror_pos] H ('high') is not double");
    };

    template <typename T>
    struct is_mirror_pos : std::false_type {  
    };

    template <typename T, typename U, typename H>
    struct is_mirror_pos<mirror_pos<T,U,H>> : std::true_type {  
    };

    template <typename T, typename U>
    struct mirror_angles{
        using min_type = T;
        using max_type = U;

        static_assert(is_min<T>::value,"[tag::mirror_angles] T is not 'min' type");
        static_assert(is_max<U>::value,"[tag::mirror_angles] U is not 'max' type");
    };
    
    template <typename T>
    struct is_mirror_angles : std::false_type {  
    };

    template <typename T, typename U>
    struct is_mirror_angles<mirror_angles<T,U>> : std::true_type {  
    };

    template <typename T>
    struct scene : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::scene] T is not string");
    };

    template <typename T>
    struct is_scene : std::false_type {  
    };

    template <typename T>
    struct is_scene<scene<T>> : std::true_type {  
    };

    template <typename T, typename U, typename H>
    struct nshe { // nodes_show_hide_element
        using scene_type = T;
        using node_type = U;
        using ar_type = H; 

        static_assert(is_scene<T>::value,"[tag::nshe] T is not 'scene' type");
        static_assert(is_node<U>::value,"[tag::nshe] U is not 'node' type");
        static_assert(is_ar<H>::value,"[tag::nshe] H is not 'ar' type");
    };

    template <typename T>
    struct is_nshe : std::false_type {  
    };

    template <typename T, typename U, typename H>
    struct is_nshe<nshe<T,U,H>> : std::true_type {  
    };

    template <typename... Nshes>
    struct nodes_show_hide {
        using type = tl::list<Nshes...>;
        static_assert(tl::all_of_if<type,is_nshe>::value,"[tag::name] not all Nshes... are nodes_show_hide_element type");
    };

    template <typename T>
    struct is_nodes_show_hide : std::false_type {  
    };

    template <typename... Nshes>
    struct is_nodes_show_hide<nodes_show_hide<Nshes...>> : std::true_type {  
    };

    template <typename T>
    struct name : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::name] T is not string");
    };

    template <typename T>
    struct is_name : std::false_type {  
    };

    template <typename T>
    struct is_name<name<T>> : std::true_type {  
    };

    template <typename T>
    struct lib : T {
        static_assert(literal::is_char_sequence<T>::value,"[tag::lib] T is not string");
    };

    template <typename T>
    struct is_lib : std::false_type {  
    };

    template <typename T>
    struct is_lib<lib<T>> : std::true_type {  
    };

    template <typename T, typename U>
    struct msg {
        using id_type = T;
        using data_type = U;

        static_assert(literal::is_char_sequence<T>::value,"[tag::msg] T is not string");
    };

    template <typename T>
    struct is_msg : std::false_type {  
    };

    template <typename T, typename U>
    struct is_msg<msg<T,U>> : std::true_type {  
    };

    template <typename... Ts>
    struct inputs {
        using type = tl::list<Ts...>;
        static_assert(tl::all_of_if<type,is_msg>::value,"[tag::inputs] not all Ts... are 'msg' type");
    };

    template <typename T>
    struct is_inputs : std::false_type {  
    };

    template <typename... Ts>
    struct is_inputs<inputs<Ts...>> : std::true_type {  
    };

    template <typename... Ts>
    struct outputs {
        using type = tl::list<Ts...>;
        static_assert(tl::all_of_if<type,is_msg>::value,"[tag::outputs] not all Ts... are 'msg' type");
    };

    template <typename T>
    struct is_outputs : std::false_type {  
    };

    template <typename... Ts>
    struct is_outputs<outputs<Ts...>> : std::true_type {  
    };

    template <typename Inputs, typename Outputs> 
    struct communication {
        using inputs_type = Inputs;
        using outputs_type = Outputs;

        static_assert(is_inputs<Inputs>::value,"[tag::communication] Inputs is not 'inputs' type");
        static_assert(is_outputs<Outputs>::value,"[tag::communication] Outputs is not 'outputs' type");
    };

    template <typename T>
    struct is_communication : std::false_type {  
    };

    template <typename Inputs, typename Outputs>
    struct is_communication<communication<Inputs,Outputs>> : std::true_type {  
    };

    template <typename T, typename U, typename H, typename G>
    struct zone {
        using name_type = T;
        using width_type = U;
        using height_type = H;
        using mirror_pos_type = G;

        static_assert(is_name<T>::value,"[tag::zone] T is not 'name' type");
        static_assert(is_width<U>::value,"[tag::zone] U is not 'width' type");
        static_assert(is_height<H>::value,"[tag::zone] H is not 'height' type");
        static_assert(is_mirror_pos<G>::value,"[tag::zone] G is not 'mirror_pos' type");
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

    template <typename T>
    struct is_config : std::false_type {  
    };

    template <typename... Ts>
    struct is_config<config<Ts...>> : std::true_type {  
    };

    template <typename Name, typename Lib, typename Config, typename Communication>
    struct anode {
        using name_type = Name;
        using lib_type = Lib;
        using config_type = Config;
        using communication_type = Communication;

        static_assert(is_name<Name>::value,"[tag::anode] Name is not 'name' type");
        static_assert(is_lib<Lib>::value,"[tag::anode] Lib is not 'lib' type");
        static_assert(is_config<Config>::value,"[tag::anode] Config is not 'config' type");
        static_assert(is_communication<Communication>::value,"[tag::anode] Communication is not 'communication' type");
    };

//////////

    template <typename Source, template <typename> class Condition>
    struct get;

    template <typename Source, template <typename> class Condition>
    using get_t = typename get<Source,Condition>::type;

    template <template <typename> class Condition, template <typename...> class TListHost, typename... Ts>
    struct get<TListHost<Ts...>,Condition> {
        using type = tl::front_t<tl::find_if_t<typename TListHost<Ts...>::type, Condition>>;
    };

    template <typename Source>
    using get_name_t = typename Source::name_type;

    template <typename Source>
    using get_width_t = typename Source::width_type;

    template <typename Source>
    using get_height_t = typename Source::height_type;

    template <typename Source>
    using get_mirror_pos_t = typename Source::mirror_pos_type;

    template <typename Source>
    using get_low_t = typename Source::low_type;

    template <typename Source>
    using get_mid_t = typename Source::mid_type;

    template <typename Source>
    using get_high_t = typename Source::high_type;

    template <typename Source>
    using get_lib_t = typename Source::lib_type;

    template <typename Source>
    using get_config_t = typename Source::config_type;

    template <typename Source>
    using get_communication_t = typename Source::communication_type;

    template <typename Source>
    using get_min_t = typename Source::min_type;

    template <typename Source>
    using get_max_t = typename Source::max_type;

    template <typename Source>
    using get_scene_t = typename Source::scene_type;

    template <typename Source>
    using get_node_t = typename Source::node_type;

    template <typename Source>
    using get_ar_t = typename Source::ar_type;

    template <typename Source>
    using get_inputs_t = typename Source::inputs_type;
    template <typename Source>
    using get_outputs_t = typename Source::outputs_type;

    template <typename Source>
    using get_id_t = typename Source::id_type;

    template <typename Source>
    using get_data_t = typename Source::data_type;

    template <typename TList, typename F, typename... Args>
    std::enable_if_t<tl::is_list<TList>::value,F> 
    for_each(F f, Args&&... args) {
        return tl::rt::for_each<TList>(std::move(f),args...);
    }

    template <typename TList, typename F, typename... Args>
    std::enable_if_t<!tl::is_list<TList>::value,F> 
    for_each(F f, Args&&... args) {
        return tl::rt::for_each<typename TList::type>(std::move(f),args...);
    }

}   // tag namespace

// clang-format on

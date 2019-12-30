/****************************************************************************
 * Copyright (C) 2019 by Apostera GmbH                                      *
 ****************************************************************************/
/**
 * @file      typelist.hpp
 * @author    Oleksandr Nikolayenko (Alexander.Nikolaenko@apostera.com)
 * @domain    ???
 * @component ???
 * @sw_unit   ???
 * @ip_type   BGIP
 * @brief     one of the central data structure in metaprogramming is the typelist, which, as its name implies, is a list containing types.
 *
 */

#pragma once

#include <type_traits>
#include <utility>

/**
 *    A typelist is a type that represents a list of types and can be manipulated by a
 *    template metaprogram. It provides the operations typically associated with a list:
 *    iterating over the elements (types) in the list, adding elements, or removing elements.
 *    However, typelists differ from most run-time data structures, such as std::list,
 *    in that they don’t allow mutation. Adding an element to a typelist, on the
 *    other hand, does not change the original typelist: Rather, adding an element to an
 *    existing typelist creates a new typelist without modifying the original.
 *
 * @see https://www.codeproject.com/Articles/1077852/TypeLists-and-a-TypeList-Toolbox-via-Variadic-Temp
 *      https://blog.galowicz.de/2016/05/08/compile_time_type_lists/
 *      http://www.tmplbook.com/, Chapter 24
 *      https://www.drdobbs.com/generic-programmingtypelists-and-applica/184403813
 */

// clang-format off

namespace tl // <-- typelist
{

///
/// A direct implementation of a typelist encodes the elements in a parameter pack
/// The elements of a list<...> are written directly as its template arguments.
/// @code
///     using empty_list = list<>;
///     using integral_types = list<boo, char, short, int, long, long long>;
/// @endcode
///

    template<typename... Ts> struct list {};

///
/// @brief checks whether T is an list<...> type.
/// @param  T requested type to be tested
/// @return the member boolean constant 'value' equal to `true` if the T is list<...>. Otherwise value is `false`.
/// @code
///     static_assert(is_list<list<std::string>>::value==true);
///     static_assert(is_list<std::string>::value==false);
/// @endcode
///
    template <typename T>
    struct is_list : std::false_type {
    }; 

    template <typename... Ts>
    struct is_list<list<Ts...>> : std::true_type {
    }; 

// Construct below is incorrect till C++17
//    template <typename T>
//    inline constexpr bool is_list_v = is_list<T>::value;

///
/// @brief `is_empty` determines whether the given typelist has no elements
/// @param TList a typelis, tl::list<type1,type2,...>
/// @return the member boolean constant 'value' equal to `true` if the TList is empty. Otherwise value is `false`.
/// @code
///     static_assert(is_empty<list<int,double,void*>>::value==false);
///     static_assert(is_empty<list<>>::value==true);
/// @endcode
///

    template<typename TList>
    struct is_empty : std::false_type {
    };

    template<>
    struct is_empty<list<>> : std::true_type {
    };

//    template <typename TList>
//    inline constexpr bool is_empty_v = is_empty<TList>::value;

///
/// @brief `size` returns number of elements in the list
/// @param TList a typelis, tl::list<type1,type2,...>
/// @return the member constant 'value' equal to number of elements in TList.
/// @code
///     static_assert(size<list<int,double,void*>>::value==3);
/// @endcode
///

    template<typename TList> struct size;

    template<typename... Ts>
    struct size<list<Ts...>> {
        static constexpr unsigned value = sizeof...(Ts);
    };

//    template <typename TList>
//    inline constexpr unsigned size_v = size<TList>::value;


///
/// @brief  Forms the logical negation of the type trait B.
/// @param B is a UnaryTypeTrait
/// @return std::bool_constant<!bool(B::value)>
/// @see https://en.cppreference.com/w/cpp/types/negation
/// @code
///     static_assert(std::is_same_v<std::true_type,negation<std::false_type>>);
/// @endcode
///

    template <typename B>
    struct negation : std::conditional_t<B::value,std::false_type,std::true_type> {
    };

//  template<class B>
//  inline constexpr bool negation_v = negation<B>::value;

///
/// @brief `any_of` checks if specified type T exists in a list of types
/// @param  T requested task to be tested
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member constant 'value' equal to `true` if at least one element of type T is in the TList. Otherwise value is `false`.
/// @code
///     any_of<list<int,char,double>,char>::value == true
/// @endcode
///

    template<typename TList, typename T> 
    struct any_of : std::false_type {
    };

    template<typename Head, typename... Tail> 
    struct any_of<list<Head,Tail...>,Head> : std::true_type {
    };

    template<typename Head, typename... Tail, typename T> 
    struct any_of<list<Head,Tail...>,T> :  any_of<list<Tail...>,T> {
    };

//    template<typename TList, typename T>
//    inline constexpr bool any_of_v = any_of<TList,T>::value;

///
/// @brief none_of checks if specified type T does not exist in a list of types
/// @param  T requested task to be tested
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member constant 'value' equal to `true` if there is no element of type T in the TList. Otherwise value is `false`.
/// @code
///     none_of<list<int,char,double>,float>::value == true
/// @endcode
///

    template<typename TList, typename T> 
    struct none_of : negation<any_of<TList,T>> {
    };

//    template<typename TList, typename T>
//    inline constexpr bool none_of_v = none_of<TList,T>::value;

///
/// @brief all_of checks if all types in the list of types are the same requested type 
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member constant 'value' equal to `true` if all types are of the requested type. Otherwise value is `false`.
/// @code
///     all_of<list<int,int,int>,int>::value == true
/// @endcode
///

    template<typename TList, typename T> 
    struct all_of;

    template<typename Uno, typename T> 
    struct all_of<list<Uno>,T> : std::is_same<Uno,T> {
    };

    template<typename T> 
    struct all_of<list<>,T> : std::false_type {
    };

    template<typename Head, typename... Tail, typename T> 
    struct all_of<list<Head,Tail...>,T> :  std::conditional_t<
            std::is_same<Head,T>::value
            ,all_of<list<Tail...>,T>
            ,std::false_type
        > {
    };

//    template<typename TList, typename T>
//    inline constexpr bool all_of_v = all_of<TList,T>::value;

///
/// @brief `any_of_if` checks if there is a type T in the typelist which meets the requirement
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @param  MetaPredicate specifies requirements for type T. 
///         It must have defintion: template <typename T> typename MetaPred { static constexpr bool value = some_operation<T> };
/// @return the member constant 'value' of boolean type equal to `true` if at least one element of type T for which MetaPred<T>::value == true is in the TList. Otherwise value is `false`.
/// @code
///         using list1 = list<double,float,const char*,void*>;
///         any_of_if<list1,std::is_integral>::value==false
/// @endcode
///

    template<typename TList, template <typename T> class MetaPredicate> 
    struct any_of_if : std::false_type {
    };

    template<typename Head, typename... Tail, template <typename T> class MetaPredicate> 
    struct any_of_if<list<Head,Tail...>,MetaPredicate> : std::conditional_t<
                         MetaPredicate<Head>::value
                        ,std::true_type
                        ,any_of_if<list<Tail...>,MetaPredicate>
        > {
    };

//    template<typename TList, template <typename T> class MetaPredicate> 
//    inline constexpr bool any_of_if_v = any_of_if<TList,MetaPredicate>::value;

///
/// @brief `none_of_if` checks if there is no type T in the typelist which meets the requirement
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @param  MetaPredicate specifies requirements for type T. 
///         It must have defintion: template <typename T> typename MetaPred { static constexpr bool value = some_operation<T> };
/// @return the member constant 'value' of boolean type equal to `false` if at least one element of type T for which MetaPred<T>::value == true is in the TList. Otherwise value is `true`.
/// @code
///         using list1 = list<double,float,const char*,void*>;
///         none_of_if<list1,std::is_integral>::value==true
/// @endcode
///

    template<typename TList, template <typename T> class MetaPredicate> 
    struct none_of_if : std::true_type {
    };

    template<typename Head, typename... Tail, template <typename T> class MetaPredicate> 
    struct none_of_if<list<Head,Tail...>,MetaPredicate> : std::conditional_t<
                         MetaPredicate<Head>::value
                        ,std::false_type
                        ,none_of_if<list<Tail...>,MetaPredicate>
        > {
    };

//    template<typename TList, template <typename T> class MetaPredicate> 
//    inline constexpr bool none_of_if_v = none_of_if<TList,MetaPredicate>::value;


///
/// @brief `all_of_if` checks if all types in the typelist meet the requirement
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @param  MetaPredicate specifies requirements for type T. 
///         It must have defintion: template <typename T> typename MetaPred { static constexpr bool value = some_operation<T> };
/// @return the member constant 'value' of boolean type equal to `true` if every element of type T is in the TList has MetaPred<T>::value==true. Otherwise value is `false`.
/// @code
///         using list1 = list<int,float,char,bool>;
///         all_of_if<list1,std::is_integral>::value==false
/// @endcode
///

    template<typename TList, template <typename T> class MetaPredicate> 
    struct all_of_if;

    template<typename T, template <typename T> class MetaPredicate> 
    struct all_of_if<list<T>,MetaPredicate> : MetaPredicate<T> {
    };

    template<template <typename T> class MetaPredicate> 
    struct all_of_if<list<>,MetaPredicate> : std::false_type {
    };

    template<typename Head, typename... Tail, template <typename T> class MetaPredicate> 
    struct all_of_if<list<Head,Tail...>,MetaPredicate> : std::conditional_t<
                         MetaPredicate<Head>::value
                        ,all_of_if<list<Tail...>,MetaPredicate>
                        ,std::false_type
        > {
    };

//    template<typename TList, template <typename T> class MetaPredicate> 
//    inline constexpr bool all_of_if_v = all_of_if<TList,MetaPredicate>::value;

///
/// @brief `any_of_from` checks if there is a type T in the typelist1 which matches to any type from typelist2
/// @param  TList1 variadic template list<T1,T2,...> 
/// @param  TList2 variadic template list<T1,T2,...> 
/// @return the member constant 'value' of boolean type equal to `true` if there is at least one match in both typelists. Otherwise value is `false`.
/// @code
///         using list1 = list<double,float,const char*,void*>;
///         using list2 = list<A,B,void*,C>;
///         any_of_from<list1,list2>::value==true
/// @endcode
///

    template<typename TList1, typename TList2> 
    struct any_of_from : std::false_type {
    };

    template<typename Head, typename... Tail, typename TList2> 
    struct any_of_from<list<Head,Tail...>,TList2> : std::conditional_t<
                 any_of<TList2,Head>::value
                ,std::true_type
                ,any_of_from<list<Tail...>,TList2>
            >  
    {};

//    template<typename TList1, typename TList2> 
//    inline constexpr bool any_of_from_v = any_of_from<TList1,TList2>::value;


///
/// @brief `none_of_from` checks if there is nothing in the typelist1 which matches to any type from typelist2
/// @param  TList1 variadic template list<T1,T2,...> 
/// @param  TList2 variadic template list<T1,T2,...> 
/// @return the member constant 'value' of boolean type equal to `true` if there no match in both typelists. Otherwise value is `false`.
/// @code
///         using list1 = list<double,float,const char*,void*>;
///         using list2 = list<A,B,void*,C>;
///         none_of_from<list1,list2>::value==false
/// @endcode
///

    template<typename TList1, typename TList2> 
    struct none_of_from : negation<any_of_from<TList1,TList2>> {
    };


//    template<typename TList1, typename TList2> 
//    inline constexpr bool none_of_from_v = none_of_from<TList1,TList2>::value;


///
/// @brief `all_of_from` checks if each element of type T from typelist1 has a match in a set enclosed by typelist2  
/// @param  TList1 variadic template list<T1,T2,...> 
/// @param  TList2 variadic template list<T1,T2,...> 
/// @return the member constant 'value' of boolean type equal to `true` if there are matches in typelist2 for every T from typelist1. Otherwise value is `false`. 
/// @code
///         using list1 = list<double,float>;
///         using list2 = list<char,double,void,float,int>;
///         all_of_from<list1,list2>::value==true
/// @endcode
///

    template<typename TList1, typename TList2> 
    struct all_of_from;

    template <>
    struct all_of_from<list<>,list<>> : std::true_type {
    };

    template <typename... Ts>
    struct all_of_from<list<>,list<Ts...>> : std::true_type {
    };

    template <typename... Ts>
    struct all_of_from<list<Ts...>,list<>> : std::false_type {
    };

    template <typename T, typename... Ts>
    struct all_of_from<list<T>,list<Ts...>> : any_of<list<Ts...>,T> {
    };

    template<typename Head, typename... Trait, typename TList2> 
    struct all_of_from<list<Head,Trait...>,TList2> : std::conditional_t<
                 any_of<TList2,Head>::value
                ,all_of_from<list<Trait...>,TList2>
                ,std::false_type
        > {
    };


//    template<typename TList1, typename TList2> 
//    inline constexpr bool all_of_from_v = all_of_from<TList1,TList2>::value;

// ----------------

///
/// @brief the `front` metafunction extracts the first element from the typelist
/// @param  TList a typelis, tl::list<type1,type2,...>
/// @return the member typename 'type' representing the first element in TList
/// @code
///     using my_list = list<double,float,long>;
///     using first1 = front_t<my_list>;        // double, syntax 1
///     using first2 = front<my_list>::type;    // double, syntax 2
///     static_assert(std::is_same_v<first1,first2>);
///     static_assert(std::is_same_v<first1,double>);
/// @endcode
///

    template<typename TList> struct front;

    template<typename Head, typename... Tail>
    struct front<list<Head, Tail...>> {
        using type = Head;
    };

    template<typename TList>
    using front_t = typename front<TList>::type;

///
/// @brief the `back` metafunction extracts the last element from the typelist:
/// @param  TList a typelis, tl::list<type1,type2,...>
/// @return the member typename 'type' representing the last element in TList
/// @code
///     using my_list = list<double,float,long>;
///     using last = back_t<my_list>;    // long
/// @endcode
///

    template<typename TList> struct back;

    template<typename Head>
    struct back<list<Head>> : front<list<Head>> {
    };

    template<typename Head, typename... Tail>
    struct back<list<Head, Tail...>> : back<list<Tail...>> {
    };

    template<typename TList>
    using back_t = typename back<TList>::type;


///
/// @brief the `pop_front` removes the first element from the typelis
/// @param  TList a typelis, tl::list<type1,type2,...>
/// @return the member typename 'type' representing the original TList without the first element
/// @code
///     using original_list = list<A,B,C>;
///     using other_list = pop_front_t<original_list>;    // list<B,C>
/// @endcode
///

    template<typename TList> struct pop_front;

    template<typename Head, typename... Tail>
    struct pop_front<list<Head, Tail...>> {
        using type = list<Tail...>;
    };

    template<typename TList>
    using pop_front_t = typename pop_front<TList>::type;

///
/// @brief the `push_front` inserts an element onto the front of the typelist
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be inserted. T can be TList
/// @return the member typename 'type' representing the typelist as a concatenation T + original TList 
/// @code
///     using original_list = list<A,B,C>;
///     using other_list1 = push_front_t<original_list,X>;    // list<X,A,B,C>
///     using other_list2 = push_front_t<original_list,original_list>;    // list<A,B,C,A,B,C>
/// @endcode
///

    template<typename TList, typename T> struct push_front;

    template<typename... Ts, typename T>
    struct push_front<list<Ts...>,T> {
        using type = list<T,Ts...>;
    };

    template<typename TList, typename T>
    using push_front_t = typename push_front<TList,T>::type;


///
/// @brief the `push_back` inserts an element onto the end of the typelist
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be inserted. T can be typelist, i.e. other TList
/// @return the member typename 'type' representing the typelist as a concatenation the original TList + T
/// @code
///     using my_list1 = push_back_t<list<signed>,unsigned>;   // list<signed,unsigned>
///     using my_list2 = push_back_t<list<A,B>,list<C,D>>;    // list<A,B,C,D>
/// @endcode
///

    template<typename TList, typename T> struct push_back;

    template<typename... Ts, typename T>
    struct push_back<list<Ts...>,T> {
        using type = list<Ts...,T>;
    };

    template<typename TList, typename T>
    using push_back_t = typename push_back<TList,T>::type;


///
/// @brief the `push_front_unique` inserts an element T onto the front of the typelist if the element of type T does not exist in the given typelist.
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be inserted
/// @return the member typename 'type' representing the typelist as a concatenation T + original TList. The resulting list has no duplication. 
/// @code
///     using original_list = list<A,B,C>;
///     using other_list = push_front_unique_t<original_list,A>;    // list<A,B,C>
/// @endcode
///
    template<typename TList, typename T> 
    struct push_front_unique {
        using type = std::conditional_t<any_of<TList,T>::value,TList,push_front_t<TList,T>>;
    };

    template<typename TList, typename T>
    using push_front_unique_t = typename push_front_unique<TList,T>::type;

///
/// @brief the `push_back_unique` inserts an element T onto the end of the typelist if the element of type T does not exist in the given typelist.
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be inserted
/// @return the member typename 'type' representing the typelist as a concatenation the original TList + T. The resulting list has no duplication. 
/// @code
///     using original_list = list<A,B,C>;
///     using other_list = push_back_unique_t<original_list,A>;    // list<A,B,C>
/// @endcode
///

    template<typename TList, typename T> 
    struct push_back_unique {
        using type = std::conditional_t<any_of<TList,T>::value,TList,push_back_t<TList,T>>;
    };

    template<typename TList, typename T>
    using push_back_unique_t = typename push_back_unique<TList,T>::type;

///
/// @brief the `push_front_if` inserts an element T onto the front of the typelist if a condition meets the requirement.
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be inserted
/// @param Condition<T> specifies the requirement to T, see example std::is_integral<T>
/// @return the member typename 'type' representing the typelist as a concatenation T + original TList if Condition<T>::value==true. 
/// @code
///     using original_list = list<A,B,C>;
///     using other_list = push_front_if_t<original_list,std::integral,bool>;    // list<bool,A,B,C>
/// @endcode
///
    template<typename TList, template <typename T> class Condition, typename T> 
    struct push_front_if {
        using type = std::conditional_t<Condition<T>::value,push_front_t<TList,T>,TList>;
    };

    template<typename TList, template <typename T> class Condition, typename T>
    using push_front_if_t = typename push_front_if<TList,Condition,T>::type;


///
/// @brief the `push_back_if` inserts an element T at the end of the typelist if a condition meets the requirement.
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be inserted
/// @param Condition<T> specifies the requirement to T, see example std::is_integral<T>
/// @return the member typename 'type' representing the typelist as a concatenation original TList + T if Condition<T>::value==true. 
/// @code
///     using original_list = list<A,B,C>;
///     using other_list = push_front_if_t<original_list,std::integral,void*>;    // list<A,B,C>
/// @endcode
///
    template<typename TList, template <typename T> class Condition, typename T> 
    struct push_back_if {
        using type = std::conditional_t<Condition<T>::value,push_back_t<TList,T>,TList>;
    };

    template<typename TList, template <typename T> class Condition, typename T>
    using push_back_if_t = typename push_back_if<TList,Condition,T>::type;

///
/// @brief `replace_front` replaces the first element in a typelist by applying new one
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param T type to be applied
/// @return the member typename 'type' representing the the original TList with replaced the first element of requested T
/// @code
///     using list1 = list<int,char,long,unsigned>;
///     using list2 = replace_front_t<list1,void>;  // list<void,char,long,unsigned>
/// @endcode
///

    template<typename TList, typename T>
    struct replace_front : push_front<pop_front_t<TList>, T> {
    };

    template<typename TList, typename T>
    using replace_front_t = typename replace_front<TList,T>::type;

///
/// @brief `nth_element` extracts a specific element from the list (zero-based indexing)
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param N the integral constant representing an element position in the TList
/// @return the member typename 'type' representing element type in TList by requested index N
/// @code
///     using my_list = list<int,char,long,unsigned>;
///     using first = nth_element_t<my_list,0>; // int
///     using last = nth_element_t<my_list,3>; // unsigned
/// @endcode
///

    template<typename TList, unsigned N>
    struct nth_element : nth_element<pop_front_t<TList>,N-1> {
    };

    template<typename TList>
    struct nth_element<TList,0> : front<TList> {
    };

    template<typename TList, unsigned N>
    using nth_element_t = typename nth_element<TList,N>::type;

///
/// @brief is_unique checks if there is not a duplication in the list of types
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member constant 'value' equal to `true` if no duplication is detected. Otherwise value is `false`.
/// @code
///     is_unique<list<int,char,short,void>>::value == true
///     is_unique<list<int,char,int>>::value == false
/// @endcode
///
    template <typename TList> 
    struct is_unique : std::true_type {
    };

    template <typename Head, typename... Tail>
    struct is_unique <list<Head,Tail...>> : std::conditional_t<
             any_of<list<Tail...>,Head>::value    
            ,std::false_type
            ,is_unique<list<Tail...>>
        > {
    };    

//    template <typename TList>
//    inline constexpr bool is_unique_v = is_unique<TList>::value;

///  
/// @brief is_same checks if all types in the typelist are the same
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member constant 'value' equal to `true` if all types are the same. Otherwise value is `false`.
/// @code
///     is_same<list<int,int,int,int>>::value == true
///     is_same<list<int,char,int>>::value == false
/// @endcode
///

    template <typename TList> struct is_same;

    template <typename Head, typename... Tail>
    struct is_same <list<Head,Tail...>> : all_of<list<Tail...>, Head> { 
    };    

//    template <typename TList>
//    inline constexpr bool is_same_v = is_same<TList>::value;


///  
/// @brief checks if the typelist contains other list as an element
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member constant 'value' equal to `true` if at least one element is of list<...> type. Otherwise value is `false`.
/// @code
///     has_nested_list<list<int,int,int,int>>::value == false
///     has_nested_list<list<int,char,list<void>,int>>::value == true
/// @endcode
///

    template <typename TList>
    struct has_nested_list : std::false_type {
    };

    template <typename Head, typename... Tail>
    struct has_nested_list<list<Head, Tail...>> : std::conditional_t <
        is_list<Head>::value
       ,std::true_type
       ,has_nested_list<list<Tail...>>
    > {
    };

//    template <typename TList>
//    inline constexpr bool has_nested_list_v = has_nested_list<TList>::value;

/// 
/// @brief reverse returns typelist with element in reverse order
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member typename 'type' representing typelist of elements in reverse order against the original TList
/// @code
///     using right_to_left = reverse_t<list<A,B,C,D>>;
///     static_assert(std::is_same_v<right_to_left,list<D,C,B,A>>);
/// @endcode
///

    template<typename TList, bool Empty = is_empty<TList>::value>
    struct reverse;

    template<typename TList>
    using reverse_t = typename reverse<TList>::type;

    template<typename TList>
    struct reverse<TList, false> : push_back<reverse_t<pop_front_t<TList>>, front_t<TList>> { 
    };

    template<typename TList>
    struct reverse<TList, true> {
        using type = TList;
    };


/// 
/// @brief enumerates all types in the typelist one by another and perform any operations on the elements within the typlelist in a particular way.
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @param  MetaFun describes transformation rule. It must meet the following defintion: template <typename> MetaFun { using type = some_operation<T> };
/// @return the member typename 'type' representing typelist with "transformed" elements from the original TList
/// @code
///     template <typename T> make_pointer {
///         using type = T*;    
///     };    
///     using list = transform_t<list<A,B,C>,make_pointer>;  // output: list<A*,B*,C*> 
/// @endcode
///

// --- Recursive Algorithms ---
//    template<typename TList, template<typename T> class MetaFun, bool Empty = is_empty<TList>::value>
//    struct transform;
//
//    template<typename TList, template<typename T> class MetaFun>
//    using transform_t = typename transform<TList, MetaFun>::type;
//
//    template<typename TList, template<typename T> class MetaFun>
//    struct transform<TList, MetaFun, false> : push_front <
//                 transform_t<pop_front_t<TList>,MetaFun>
//                ,typename MetaFun<front_t<TList>>::type
//            >
//    {
//    };
//
//    template<typename TList, template<typename T> class MetaFun>
//    struct transform<TList, MetaFun, true> {
//        using type = TList;
//    };

// ---  Optimized 'transform' with Pack Expansions ---
    template<typename TList, template<typename T> class MetaFun>
    struct transform;

    template<typename... Ts, template<typename T> class MetaFun>
    struct transform<list<Ts...>,MetaFun> {
        using type = list<typename MetaFun<Ts>::type...>;
    };

    template<typename TList, template<typename T> class MetaFun>
    using transform_t = typename transform<TList, MetaFun>::type;

/// 
/// @brief combines all of the elements in the typelist into a single resulting value.
///     The `accumulate` algorithm takes a typelist TList with elements T1 ,T2 , ..., TN
///     an initial type I, and a metafunction MetaFun , which accepts two types and returns a type. 
///     It returns MetaFun(MetaFun (MetaFun (...MetaFun(I, T1), T2), ...), TN),
///     where at the i-th step in the accumulation MetaFun is applied to the result of the previous i−1 steps and Ti .
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @param  MetaFun describes accumulator rule. 
///         It must meet the following defintion: template <typename ResultType, typename T> MetaFun { using type = some_operation<ResultType,T> };
/// @param  I initial type. 
/// @return the member typename 'type' representing accumulated type MetaFun<...>::type
/// @see run-time analog: https://en.cppreference.com/w/cpp/algorithm/accumulate    
/// @code
///         template <typename T1, typename T2>
///         struct filter { // selects only integral types
///             using type = std::conditional_t<std::is_integral<T2>::value, push_back_t<T1,T2>, T1>;
///         };
///         using input = list<unsigned, double, long, float, void, char*, short>;
///         using output = accumulate_t<input, filter, list<>>;   // list<unsigned, long, short>
/// @endcode
///

   template<
        typename TList
       ,template<typename ResultT, typename T> class MetaFun
       ,typename I
       ,bool = is_empty<TList>::value
       >
   struct accumulate;

   template<typename TList, template<typename ResultT, typename T> class MetaFun, typename I>
   struct accumulate<TList, MetaFun, I, false> : accumulate<
                                                        pop_front_t<TList>
                                                       ,MetaFun
                                                       ,typename MetaFun<I, front_t<TList>>::type
                                                   > {
   };

   template<typename TList, template<typename ResultT, typename T> class MetaFun, typename I>
   struct accumulate<TList, MetaFun, I, true> {
       using type = I;
   };

   template<typename TList, template<typename ResultT, typename T> class MetaFun, typename I>
   using accumulate_t = typename accumulate<TList, MetaFun, I>::type;


/// 
/// @brief eliminates all but the first element of type T from the typelist 
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member typename 'type' representing typelist of elements with no duplications
/// @code
///     using output = unique_t<list<A,B,C,A,D,B>>;
///     static_assert(std::is_same_v<output,list<A,B,C,D>>);
/// @endcode
///

   template <typename TList>
   struct unique : accumulate<TList, push_back_unique, list<>> {
   };

   template<typename TList>
   using unique_t = typename unique<TList>::type;

/// 
/// @brief eliminates all but the first element of type T from the input typelist and populates the output typelist of elements in reverse order 
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @return the member typename 'type' representing typelist of elements with no duplications. Resulting typelist has elements in reverse order.
/// @code
///     using output = unique_reverse_t<list<A,B,C,A,D,B>>;
///     static_assert(std::is_same_v<output,list<D,C,B,A>>);
/// @endcode
///

   template <typename TList>
   struct unique_reverse : accumulate<TList,push_front_unique,list<>> {
   };

   template<typename TList>
   using unique_reverse_t = typename unique_reverse<TList>::type;


///
/// @brief inserts types from a typelist onto the end of the other one in a row
/// @param TList1 a destination typelis, tl::list<type1,type2,...>
/// @param TList2 a source typelis, tl::list<type1,type2,...tl::list<type3,type4,...>>
///         TList2 is to be inserted. If it contains nested lists than their elements are copied linearly (nested lists are expanded) 
/// @return the member typename 'type' representing the typelist as a concatenation TList1 + singular types of TList2
/// @code
///     using destination = list<void>;
///     using source = list<int,list<char,bool>,list<float,double>>;
///     using composition = push_back_termwise_t<destination,source>; // list<void,int,char,bool,float,double>
/// @endcode
///

   template<typename TList, typename T>
   struct push_back_termwise : push_back<TList, T> {
   };

   template <typename TList1, typename... Ts>
   struct push_back_termwise<TList1, list<Ts...>> : accumulate<list<Ts...>, push_back_termwise, TList1> {
   };

   template <typename TList1>
   struct push_back_termwise<TList1, list<>> {
      using type = TList1;
   };

   template<typename TList1, typename TList2>
   using push_back_termwise_t = typename push_back_termwise<TList1, TList2>::type;


///
/// @brief expands input typelist and makes it linear
/// @param TList a typelis, tl::list<type1,type2,...>
///         If it contains nested lists than they will be expanded
/// @return the member typename 'type' representing the linear typelist (no nested typelists)
/// @code
///      using my_list = linear_list_t<list<list<List<A,B>>>,C>;  // list<A,B,C>
/// @endcode
///

   template<typename TList>
   struct linear_list : push_back_termwise<list<>, TList> {
   };

   template<typename TList>
   using  linear_list_t = typename  linear_list<TList>::type;


///
/// @brief concatenates types from two typelists
/// @param TList1 a first typelis, tl::list<type1,type2,...>
/// @param TList2 a second typelis, tl::list<typeA,typeB,...>
/// @return the member typename 'type' representing the typelist as a concatenation of types from both typelists 
/// @code
///     using first = list<void,int>;
///     using second = list<char,bool>;
///     using composition = concatenate_t<first,second>; // list<void,int,char,bool>
/// @endcode
///

    template <typename TList1, typename TList2>
    struct concatenate;

    template <typename... Ts, typename... Us>
    struct concatenate<list<Ts...>,list<Us...>> {
        using type = list<Ts...,Us...>;
    };

    template<typename TList1, typename TList2>
    using concatenate_t = typename concatenate<TList1, TList2>::type;


///
/// @brief copies types from variadic number of typelists
/// @param TList parameter pack of typelists 
/// @return the member typename 'type' representing the typelist as a concatenation of types from every typelists as an input 
/// @code
///     using first = list<void,int>;
///     using second = list<char,bool>;
///     using third = list<float,double>;
///     using composition = copy_t<first,second,third>; // list<void,int,char,bool,float,double>
/// @endcode
///

    template <typename... TList>
    struct copy;

    template <typename... TList>
    using copy_t = typename copy<TList...>::type;;

    template <typename TList1, typename TList2>
    struct copy<TList1, TList2> {
        using type = concatenate_t<TList1,TList2>;
    };

    template <typename Head, typename... Tail>
    struct copy<Head, Tail...> : copy<Head, copy_t<Tail...>> {
    };

/// 
/// @brief  searches for types in the typelist for which Condition<T> returns true
/// @param  TList variadic template list<T1,T2,...> representing a list of types
/// @param  Condition - unary meta function which specifies search creteria for the requested type. It must meet the following defintion: template <typename T> Condition { bool value = some_operation<T> };
/// @return the member typename 'type' representing typelist with types for which Condtition<T>::value==true
/// @code
///     using list = find_if_t<list<list<A>,int,list<B,C>,bool,void>,is_list>;  // output: list<list<A>,list<B,C>> 
/// @endcode
///

    template<typename TList, template<typename T> class Condition>
    struct find_if {
        template <typename ResultType, typename T>
        using push_if = push_back_if<ResultType,Condition,T>;
        using type = accumulate_t<TList,push_if,list<>>;
    };

    template<typename TList, template<typename T> class Condition>
    using  find_if_t = typename  find_if<TList,Condition>::type;

namespace rt   // run-time 
{

///
/// @brief applies the given function object f to every type in the typelist, in order.
/// @param TList a typelis, tl::list<type1,type2,...>
/// @param f function object, to be applied
///      The signature of the function should be equivalent to the following
///      void fun(T*, Args...);
///      where
///      T* - nullptr of T type, an element from the typelist. T* (first parameter) is used as a dummy to make overloading possible 
///      Args - arguments (any number of any types) you want to pass to the given function object
/// @return std::move(f)
/// @code
///         using composition = list<int, double, const char*>;
///         struct visitor {
///            void operator()(int*, int a1, double a2, const char* a3) {
///               collector.push_back(string{ "I'm `int`: " } +to_string(a1));
///            }
///            void operator()(double*, int a1, double a2, const char* a3) {
///               collector.push_back(string{ "I'm `double`: " } +to_string(a2));
///            }
///            void operator()(const char**, int a1, double a2, const char* a3) {
///               collector.push_back(string{ "I'm `string`: " } +a3);
///            }
///            vector<string> collector;
///         };
///         auto out = for_each<composition>(visitor{}, 1, .1, "Hello, World!").collector;
///         // output: "I'm `int`: 1" "I'm `double`: .1" "I'm `string`: Hello, World!"
/// @endcode
///

   template <typename TList> struct visit;

   template <>
   struct visit <list<>> {
      template <typename F, typename... Args>
      F operator()(F f, Args&&...) {
         return std::move(f);
      }
   };

   template <typename Head, typename... Tail>
   struct visit<list<Head, Tail...>> {
      template <typename F, typename... Args >
      F operator()(F f, Args&&... args) {
         f((Head*)nullptr, std::forward<Args>(args)...);
         return visit<list<Tail...>>()(std::move(f), std::forward<Args>(args)...);
      }
   };

   template <typename TList, typename F, typename... Args>
   F for_each(F f, Args&&... args) {
      return visit<TList>()(std::move(f), std::forward<Args>(args)...);
   }

}  // namespace rt   


namespace unit_test
{
    /**
     * Temporary location. This section should be moved onto most suitable place
     * It contains some examples and tests about typelist usage 
    */ 

    using integral_types = list<signed char, short, int, long, long long>;
    using empty_list = list<>;

    inline void tl_negation() {
        static_assert(negation<std::true_type>::value==false,"tl_negation 1");
        static_assert(negation<std::false_type>::value==std::true_type::value,"tl_negation 2");
    }

    inline void tl_islist() {
        static_assert(is_list<integral_types>::value,"tl_islist assert 1");
        static_assert(is_list<empty_list>::value,"tl_islist assert 2");
        static_assert(!is_list<int>::value,"tl_islist assert 3");
    }

    inline void tl_front_back() {
        using first = front_t<integral_types>;
        static_assert(std::is_same<first,signed char>::value,"tl_front_back assert 1");
        static_assert(size<integral_types>::value==5,"tl_front_back assert 2");

        using last = back_t<integral_types>;
        static_assert(std::is_same<last,long long>::value,"tl_front_back assert 3");
    }

    inline void tl_pop_front()  {
        using another_list = pop_front_t<pop_front_t<integral_types>>;
        using first = front_t<another_list>;
        static_assert(std::is_same<first,int>::value,"tl_pop_front assert 1");
    }


    inline void tl_push_front() {
        using another_list = push_front_t<integral_types,float>;
        using first = front_t<another_list>;
        static_assert(std::is_same<first,float>::value,"tl_push_front assert 1");

        using another_list2 = 
        push_back_t<
            push_back_t<empty_list,float
            >,int
        >;
        static_assert(std::is_same<another_list2,list<float,int>>::value,"tl_push_front assert 2");

        using l1 = list<int,short,char>;
        using l2 = list<const char*, void*>;
        using another_list3 = push_front_t<l1,l2>; 
        static_assert(std::is_same<another_list3,list<list<const char*,void*>,int,short,char>>::value,"tl_push_front assert 3");

        using another_list4 = push_back_t<l1,l2>; 
        static_assert(std::is_same<another_list4,list<int,short,char,list<const char*,void*>>>::value,"tl_push_front assert 4");
    }

    inline void tl_push_unique() {
        using another_list1 = push_front_unique_t<integral_types,long>;
        static_assert(std::is_same<another_list1,integral_types>::value,"tl_push_unique 1");
        using another_list2 = push_back_unique_t<integral_types,short>;
        static_assert(std::is_same<another_list2,integral_types>::value,"tl_push_unique 2");
    }    

    inline void tl_replace_front()  {
        using another_list = replace_front_t<integral_types,double>;
        using first = front_t<another_list>;
        static_assert(std::is_same<first,double>::value,"replace_front assert 1");
    }

    inline void tl_nth_element()  {
        using second = nth_element_t<integral_types,1>;
        static_assert(std::is_same<second,short>::value,"tl_nth_element assert 1");
        using first = nth_element_t<integral_types,0>;
        static_assert(std::is_same<first,signed char>::value,"tl_nth_element assert 2");
        using last = nth_element_t<integral_types,4>;
        static_assert(std::is_same<last,long long>::value,"tl_nth_element assert 3");
    }

    inline void tl_empty_size() {
        static_assert(!is_empty<integral_types>::value,"tl_empty_size assert 1");
        static_assert(size<integral_types>::value==5,"tl_empty_size assert 2");
        using another_list = 
            pop_front_t<
                pop_front_t<
                    pop_front_t<
                        pop_front_t<
                            pop_front_t<integral_types>
                        >
                    >
                >
            >;                
        static_assert(is_empty<another_list>::value,"tl_empty_size assert 3");
        static_assert(size<another_list>::value==0,"tl_empty_size assert 4");

        using another_list2 = push_back_t<push_back_t<another_list,int>,void*>;
        using last = nth_element_t<another_list2,1>;
        static_assert(std::is_same<last,void*>::value,"tl_empty_size assert 5");
    }

    inline void tl_reverse()  {
        using another_list = reverse_t<integral_types>;        
        using first = nth_element_t<another_list,0>;
        static_assert(std::is_same<first,long long>::value,"tl_reverse assert 1");
        using last = nth_element_t<another_list,4>;
        static_assert(std::is_same<last,signed char>::value,"tl_reverse assert 2");
    }

    inline void tl_any_none_all() {
        static_assert(any_of<integral_types,short>::value,"tl_any_none_all assert 1");
        static_assert(!any_of<integral_types,void*>::value,"tl_any_none_all assert 2");
        static_assert(!any_of<empty_list,void*>::value,"tl_any_none_all assert empty");

        static_assert(!none_of<integral_types,short>::value,"tl_any_none_all assert 3");
        static_assert(none_of<integral_types,void*>::value,"tl_any_none_all assert 4");
        static_assert(none_of<empty_list,void*>::value,"tl_any_none_all assert empty");

        static_assert(!all_of<integral_types,int>::value,"tl_any_none_all assert 5");
        static_assert(!all_of<empty_list,void>::value,"tl_any_none_all assert empty");
        using many_ints = list<int,int,int,int,int,int,int,int,int,int>;
        static_assert(all_of<many_ints,int>::value,"tl_any_none_all assert 6");
        static_assert(is_same<many_ints>::value,"tl_any_none_all assert 7");
    }    

    inline void tl_is_unique() {
        static_assert(is_unique<integral_types>::value,"tl_unique assert 1");
        using another_list = push_back_t<integral_types,long>;
        static_assert(!is_unique<another_list>::value,"tl_unique assert 2");
    }    

   template <typename T>
   struct make_pointer {
        using type = T*;
   };

   inline void tl_transform() {
        using other_list = transform_t<integral_types,make_pointer>;
        static_assert(std::is_same<other_list,list<signed char*, short*, int*, long*, long long*>>::value,"tl_transform assert 1");
   }

   template <typename T1, typename T2>
   struct larger_by_size {
      using type = std::conditional_t<sizeof(T1) >= sizeof(T2), T1, T2>;
   };

   template <typename T1, typename T2>
   struct int_filter {
        using type = std::conditional_t<std::is_integral<T2>::value, push_back_t<T1,T2>, T1>;
   };

    inline void tl_accumulate() {
        using largest = accumulate_t<
                 pop_front_t<integral_types>
                ,larger_by_size
                ,front_t<integral_types>
        >; 
        static_assert(std::is_same<largest,long>::value,"tl_accumulate assert 1");
        static_assert(sizeof(long) == sizeof(long long),"tl_accumulate assert 2");

        // With `accumulate` in hand, we can reverse a typelist using
        using other1 = accumulate_t<integral_types,push_front,list<>>;
        using other2 = reverse_t<integral_types>;
        static_assert(std::is_same<other1,other2>::value,"tl_accumulate assert 3");

        // and select only integral types from input list of arbitrary types
        using input = list<unsigned, double, long, float, void, char*, short>;
        using output = accumulate_t<input,int_filter,list<>>;
        static_assert(std::is_same<output,list<unsigned, long, short>>::value,"tl_accumulate assert 4");
    }    

    inline void tl_accumulate_nested() {
        using l1 = list<int,char>;
        using l2 = list<double,float>;
        using l1l2 = accumulate_t<l2,push_back,l1>;
        static_assert(std::is_same<l1l2,list<int,char,double,float>>::value,"tl_accumulate_nested assert 1");
    }    

    inline void tl_unique() {
        using input = list<int,int,char,void,float,void*,void>;
        using output1 = unique_t<input>;
        using output2 = unique_reverse_t<input>;
        static_assert(std::is_same<output1,list<int,char,void,float,void*>>::value,"tl_unique assert 1");
        static_assert(std::is_same<output2,list<void*,float,void,char,int>>::value,"tl_unique assert 2");
    }

    inline void tl_has_nested_list() {
        static_assert(!has_nested_list<empty_list>::value, "tl_has_nested_list assert 1");
        static_assert(!has_nested_list<integral_types>::value, "tl_has_nested_list assert 2");
        static_assert(has_nested_list<list<integral_types>>::value, "tl_has_nested_list assert 3");
        static_assert(has_nested_list<list<int,bool,list<char,void>>>::value, "tl_has_nested_list assert 4");
    }

    inline void tl_push_back_termwise() {
        using l1 = push_back_termwise_t<list<int,int>,list<bool,bool>>;
        static_assert(std::is_same<l1,list<int,int,bool,bool>>::value, "tl_push_back_termwise assert 1");

        using l2 = push_back_termwise_t<list<int,int>,list<>>;
        static_assert(std::is_same<l2,list<int,int>>::value, "tl_push_back_termwise assert 2");

        using l3 = push_back_termwise_t<list<int,int>,bool>;
        static_assert(std::is_same<l3,list<int,int,bool>>::value, "tl_push_back_termwise assert 3");

        using l4 = push_back_termwise_t<list<>,list<void,list<bool,int>>>;
        static_assert(std::is_same<l4,list<void,bool,int>>::value, "tl_push_back_termwise assert 4");

        using l5 = push_back_termwise_t<list<char>,list<void,list<bool,int>,void>>;
        static_assert(std::is_same<l5,list<char,void,bool,int,void>>::value, "tl_push_back_termwise assert 5");

        using l6 = push_back_termwise_t<list<>,list<list<list<void*>>>>;
        static_assert(!has_nested_list<l6>::value, "tl_push_back_termwise assert 6");
        static_assert(std::is_same<l6,list<void*>>::value, "tl_push_back_termwise assert 7");
    }

    inline void tl_linear_list() {
        using l1 = linear_list_t<list<list<list<void>>>>;
        static_assert(std::is_same<l1,list<void>>::value, "tl_linear_list assert 1");

        using l2 = linear_list_t<list<empty_list,empty_list,empty_list,empty_list>>;
        static_assert(std::is_same<l2,list<>>::value, "tl_linear_list assert 2");
    }

    inline void tl_push_front_if() {
        using output1 = push_front_if_t<integral_types,std::is_integral,bool>;
        static_assert(std::is_same<output1,push_front_t<integral_types,bool>>::value, "tl_push_front_if 1");

        using output2 = push_front_if_t<integral_types,std::is_integral,float>;
        static_assert(!std::is_same<output2,push_front_t<integral_types,float>>::value, "tl_push_front_if 2");

        using output3 = push_back_if_t<list<int>,is_list,float>;
        static_assert(std::is_same<output3,list<int>>::value, "tl_push_front_if 3");

        using output4 = push_back_if_t<list<int>,is_list,list<float>>;
        static_assert(std::is_same<output4,list<int,list<float>>>::value, "tl_push_front_if 4");
    }

    inline void tl_find_if() {
        using output = find_if_t<integral_types,std::is_integral>;
        static_assert(std::is_same<output,integral_types>::value, "tl_find_if 1");
        static_assert(tl::size<integral_types>::value==tl::size<output>::value, "tl_find_if 2");

        using input2 = list<list<int,int>,void,list<short,short>,bool,char>;
        using output2 = find_if_t<input2,is_list>;
        static_assert(std::is_same<output2,list<list<int,int>,list<short,short>>>::value, "tl_find_if 3");
    }


    inline void tl_copy() {
        using l1 = list<int,char>;
        using l2 = list<void,bool>;
        static_assert(std::is_same<concatenate_t<l1,l2>,list<int,char,void,bool>>::value,"tl_copy assert 1");
        static_assert(std::is_same<copy_t<l1,l2>,list<int,char,void,bool>>::value,"tl_copy assert 2");
        static_assert(std::is_same<copy_t<l1,l2,l2,l1>,list<int,char,void,bool,void,bool,int,char>>::value,"tl_copy assert 3");
    }    

    inline void tl_any_none_all_of_if() {
        using my_list = list<double*,float*,const char*,void*>;
        static_assert(any_of_if<my_list,std::is_integral>::value==false,"tl_any_none_all_of_if assert 1");
        static_assert(any_of_if<integral_types,std::is_integral>::value==true,"tl_any_none_all_of_if assert 2");
        static_assert(any_of_if<empty_list,std::is_integral>::value==false,"tl_any_none_all_of_if assert 3");
        static_assert(none_of_if<my_list,std::is_integral>::value==true,"tl_any_none_all_of_if assert 4");
        static_assert(none_of_if<integral_types,std::is_integral>::value==false,"tl_any_none_all_of_if assert 5");
        static_assert(none_of_if<empty_list,std::is_integral>::value==true,"tl_any_none_all_of_if assert 6");
        static_assert(all_of_if<integral_types,std::is_integral>::value==true,"tl_all_none_all_of_if assert 7");
        static_assert(all_of_if<empty_list,std::is_integral>::value==false,"tl_any_none_all_of_if assert 8");
        static_assert(all_of_if<my_list,std::is_pointer>::value==true,"tl_any_none_all_of_if assert 9");
    }


    inline void tl_any_none_all_of_from() {
        static_assert(any_of_from<integral_types,list<void*,const char*,long,void>>::value,"tl_any_none_all_of_from 1");
        static_assert(none_of_from<integral_types,list<void*,const char*,long,void>>::value==false,"tl_any_none_all_of_from 2");
        static_assert(any_of_from<empty_list,list<void*,const char*,long,void>>::value==false,"tl_any_none_all_of_from 3");
        static_assert(none_of_from<empty_list,list<void*,const char*,long,void>>::value==true,"tl_any_none_all_of_from 4");
    
        using list1 = list<double,float>;
        using list2 = list<char,double,void,float,int>;
        static_assert(all_of_from<list1,list2>::value==true, "tl_any_none_all_of_from 5");
    }

    /*
    inline void tl_for_each() {
        struct visitor {
            void operator()(int*, int a1, double a2, const char* a3 ) { 
                collector.push_back(string{"I'm `int`: "} + to_string(a1));
            }
            void operator()(double*, int a1, double a2, const char* a3) { 
                collector.push_back(string{ "I'm `double`: " } +to_string(a2));
            }
            void operator()(const char**, int a1, double a2, const char* a3) {
                collector.push_back(string{ "I'm `string`: " } + a3);
            }
            vector<string> collector;
        };

        using composition = list<int,double,const char*>;
        auto out = for_each<composition>(visitor{}, 1, .1, "Hello, World!").collector;
        for(auto s:out)
            cout << s << endl;  

    }    
    */

}   // end of unit_test namespace


}   // namespace tl, tl = typelist

// clang-format on


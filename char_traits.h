#pragma once

#include <type_traits>
#include <utility>

// clang-format off

namespace char_traits
{
   template <char ch>
   struct is_sign : std::conditional_t< 
         ch == '-' || ch == '+'
         ,std::true_type
         ,std::false_type
      >{
   };

   template <char ch>
   struct is_floating_point_sign : std::conditional_t< 
         ch == '.' || ch == 'e' || ch == 'E' || ch == 'p' || ch == 'P'
         ,std::true_type
         ,std::false_type
      >{
   };

   template <char ch>
   struct is_digit : std::conditional_t< 
         ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5'
                  || ch == '6' || ch == '7' || ch == '8' || ch == '9'
                  || is_sign<ch>::value
         ,std::true_type
         ,std::false_type
      >{
   };

   template <char ch>
   struct is_xdigit : std::conditional_t< 
         is_digit<ch>::value ||
         ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E' || ch == 'F' ||
         ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'x' || ch == 'X'
         ,std::true_type
         ,std::false_type
      >{
   };

   template <char ch, char... chars>
   struct is_digits {
      static constexpr bool value = is_digits<ch>::value && is_digits<chars...>::value;
   };

   template <char ch>
   struct is_digits<ch> : is_digit<ch> {
   };

   template <char ch, char... chars>
   struct is_xdigits {
      static constexpr bool value = is_xdigits<ch>::value && is_xdigits<chars...>::value;
   };

   template <char ch>
   struct is_xdigits<ch> : is_xdigit<ch> {
   };

   template <char ch, char... chars>
   struct is_floating_point_digits {
      static constexpr bool value = is_floating_point_digits<ch>::value && is_floating_point_digits<chars...>::value;
   };

   template <char ch>
   struct is_floating_point_digits<ch> {
      static constexpr bool value = is_xdigit<ch>::value || is_floating_point_sign<ch>::value;
   };

} // char_traits namespace

// clang-format on


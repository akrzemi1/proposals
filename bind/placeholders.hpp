#ifndef PLACEHOLDERS_HPP
#define PLACEHOLDERS_HPP

#include <functional>
#include <type_traits>
#include "placeholder_traits.hpp"

namespace functional
{
  struct all_placeholder {};

  template<int N>
  struct from_placeholder 
  {
    static_assert(N > 0, "Stating parameter index must be positve.");
  };
  
  namespace placeholders
  {
    using namespace std::placeholders;

    constexpr all_placeholder _all{};

    template<int N>
    constexpr from_placeholder<N> _from{};
  }

  template<>
  struct is_placeholder<all_placeholder>
   : std::integral_constant<int, 1>
  {};

  template<int ArgCount>
  struct parameter_indexes<all_placeholder, ArgCount>
    : type_traits::make_integer_range<int, 1, ArgCount + 1>
  {
    static_assert(ArgCount > 0, "Argument count must be positive");
  };

  template<int N>
  struct is_placeholder<from_placeholder<N>>
    : std::integral_constant<int, (N > 0)>
  {};

  template<int N, int ArgCount>
  struct parameter_indexes<from_placeholder<N>, ArgCount>
    : type_traits::make_integer_range<int, N, ArgCount + 1>
  {
    static_assert(ArgCount > 0, "Argument count must be positive");
    static_assert(N <= ArgCount + 1, "To few argument provided.");
  };
}

#endif //PLACEHOLDERS_HPP

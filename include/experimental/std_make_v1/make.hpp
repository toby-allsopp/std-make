// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// (C) Copyright 2014 Vicente J. Botet Escriba

#ifndef VIBOES_STD_EXPERIMENTAL_FUNDAMENTALS_V2_MAKE_HPP
#define VIBOES_STD_EXPERIMENTAL_FUNDAMENTALS_V2_MAKE_HPP

#include <utility>
#include <type_traits>

#if defined VIBOES_STD_EXPERIMENTAL_FACTORIES_USE_OPTIONAL
#include <optional.hpp>
#endif

namespace std
{
namespace experimental
{
#if ! defined VIBOES_STD_EXPERIMENTAL_FACTORIES_USE_OPTIONAL
  constexpr struct in_place_t{} in_place{};
#endif

inline namespace fundamental_v2
{
  template <template <class ...> class M>
  struct type_constructor {
    template <class T>
    using rebind = M<T>;
  };

  template <class T=void>
  struct type {};

  struct _t {};

  template <template <class ...> class M>
  auto make() -> decltype( make(type<M<void>>{}) )
  {
    return make(type<M<void>>{});
  }

  template <template <class ...> class M, int = 0, int..., class X>
  auto make(X&& x) -> decltype( make(type<M<typename std::decay<X>::type>>{}, std::forward<X>(x)) )
  {
    return make(type<M<typename std::decay<X>::type>>{}, std::forward<X>(x));
  }

  template <class M, int = 0, int..., class X>
  auto make(X&& x) -> decltype(make(type<M>{}, std::forward<X>(x)))
  {
    return make(type<M>{}, std::forward<X>(x));
  }

  template <class M, class ...Args>
  auto make(Args&& ...args) -> decltype(make(type<M>{}, in_place, std::forward<Args>(args)...))
  {
    return make(type<M>{}, in_place, std::forward<Args>(args)...);
  }

  // default customization point for constructor from X
  template <class M>
  M make(type<M>)
  {
    return M();
  }

  // default customization point for constructor from X
  template <class M, class X>
  M make(type<M>, X&& x)
  {
    return M(std::forward<X>(x));
  }

  // default customization point for in_place constructor
  template <class M, class ...Args>
  M make(type<M>, in_place_t, Args&& ...args)
  {
    return M(in_place, std::forward<Args>(args)...);
  }

}
}
}

#endif // VIBOES_STD_EXPERIMENTAL_FUNDAMENTALS_V2_MAKE_HPP

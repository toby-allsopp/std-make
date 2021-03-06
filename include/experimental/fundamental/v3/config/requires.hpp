// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2015 Vicente J. Botet Escriba

#ifndef JASEL_EXPERIMENTAL_V3_EXPECTED_DETAIL_REQUIRES_HPP
#define JASEL_EXPERIMENTAL_V3_EXPECTED_DETAIL_REQUIRES_HPP

// todo move to config file
#include <type_traits>

namespace std
{
namespace experimental
{
inline namespace fundamental_v3
{
  namespace expected_detail {
      enum class enabler {};
  }
}}
}

# define JASEL_REQUIRES(...) typename std::enable_if<__VA_ARGS__, int>::type = 0
# define JASEL_T_REQUIRES(...) typename = typename std::enable_if<(__VA_ARGS__), std::experimental::expected_detail::enabler>::type

// This is needed to make the condition dependent
# define JASEL_0_REQUIRES(...) \
  template< \
  bool B = (__VA_ARGS__), \
  typename std::enable_if<B, int>::type = 0 \
  >

#endif // header

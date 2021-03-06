// Copyright (C) 2016 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef JASEL_EXAMPLE_FRAMEWORK_STD_UTILITY_HPP
#define JASEL_EXAMPLE_FRAMEWORK_STD_UTILITY_HPP

#if __cplusplus >= 201402L
#include "../mem_usage.hpp"
#include <utility>

namespace std
{
  template <typename T, typename U>
  constexpr auto mem_usage(const std::pair<T, U>& v) noexcept
  -> decltype( experimental::mem_usage_able::mem_usage(v.first) + experimental::mem_usage_able::mem_usage(v.second) )
  {
    return experimental::mem_usage_able::mem_usage(v.first)
     + experimental::mem_usage_able::mem_usage(v.second)
     + sizeof(v)
     - sizeof(v.first)
     - sizeof(v.second);
  }
}

#endif

#endif

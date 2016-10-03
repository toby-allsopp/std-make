// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// (C) Copyright 2014 Vicente J. Botet Escriba

#ifndef JASEL_EXPERIMENTAL_V3_EXPECTED_UNEXPECTED_HPP
#define JASEL_EXPERIMENTAL_V3_EXPECTED_UNEXPECTED_HPP

#include <experimental/fundamental/v3/expected/config.hpp>
#include <experimental/fundamental/v3/expected/detail/constexpr_utility.hpp>
#include <experimental/fundamental/v3/expected/detail/requires.hpp>

#ifdef BOOST_EXPECTED_USE_BOOST_HPP
#include <boost/exception_ptr.hpp>
//#include <boost/type_traits.hpp>
#endif

#include <exception>
#include <utility>
#include <type_traits>

namespace std
{
namespace experimental
{
inline namespace fundamental_v3
{

  template <typename ErrorType = exception_ptr>
  class unexpected_type
  {
    ErrorType error_;
  public:
    unexpected_type() = delete;

    BOOST_EXPECTED_0_REQUIRES(is_copy_constructible<ErrorType>::value)
    BOOST_FORCEINLINE BOOST_CONSTEXPR explicit unexpected_type(ErrorType const& e) :
      error_(e)
    {
    }
    BOOST_EXPECTED_0_REQUIRES(is_move_constructible<ErrorType>::value)
    BOOST_FORCEINLINE BOOST_CONSTEXPR explicit unexpected_type(ErrorType&& e) :
      error_(move(e))
    {
    }
#if ! defined BOOST_EXPECTED_NO_CXX11_RVALUE_REFERENCE_FOR_THIS

    BOOST_CONSTEXPR
    BOOST_FORCEINLINE ErrorType const& value() const&
    {
      return error_;
    }
    BOOST_EXPECTED_CONSTEXPR_IF_MOVE_ACCESSORS
    BOOST_FORCEINLINE ErrorType& value() &
    {
      return error_;
    }
    BOOST_EXPECTED_CONSTEXPR_IF_MOVE_ACCESSORS
    BOOST_FORCEINLINE ErrorType&& value() &&
    {
      return constexpr_move(error_);
    }
#else
    BOOST_CONSTEXPR
    BOOST_FORCEINLINE ErrorType const& value() const
    {
      return error_;
    }
    BOOST_FORCEINLINE ErrorType& value()
    {
      return error_;
    }
#endif
  };

  template <class E>
  BOOST_FORCEINLINE BOOST_CONSTEXPR unexpected_type<typename decay<E>::type> make_unexpected(E&& ex)
  {
    return unexpected_type<typename decay<E>::type> (forward<E>(ex));
  }

#ifdef BOOST_EXPECTED_USE_BOOST_HPP
  template <>
  struct unexpected_type<boost::exception_ptr>
  {
    boost::exception_ptr error_;
  public:
    unexpected_type() = delete;

    BOOST_FORCEINLINE explicit unexpected_type(boost::exception_ptr const& e) :
      error_(e)
    {
    }
    BOOST_FORCEINLINE explicit unexpected_type(boost::exception_ptr&& e) :
      error_(move(e))
    {
    }

    template <class E>
    BOOST_FORCEINLINE explicit unexpected_type(E e) :
      error_(boost::copy_exception(e))
    {
    }

    BOOST_FORCEINLINE boost::exception_ptr const& value() const
    {
      return error_;
    }
  };
#endif

  template <>
  struct unexpected_type<exception_ptr>
  {
    exception_ptr error_;
  public:
    unexpected_type() = delete;

    BOOST_FORCEINLINE explicit unexpected_type(exception_ptr const& e) :
      error_(e)
    {
    }

    BOOST_FORCEINLINE explicit unexpected_type(exception_ptr &&e) :
      error_(move(e))
    {
    }

    template <class E>
    BOOST_FORCEINLINE explicit unexpected_type(E e) :
      error_(make_exception_ptr(e))
    {
    }
    BOOST_FORCEINLINE exception_ptr const& value() const
    {
      return error_;
    }
  };

  template <class E>
  BOOST_CONSTEXPR bool operator==(const unexpected_type<E>& x, const unexpected_type<E>& y)
  {
    return x.value() == y.value();
  }
  template <class E>
  BOOST_CONSTEXPR bool operator!=(const unexpected_type<E>& x, const unexpected_type<E>& y)
  {
    return !(x == y);
  }

  template <class E>
  BOOST_CONSTEXPR bool operator<(const unexpected_type<E>& x, const unexpected_type<E>& y)
  {
    return x.value() < y.value();
  }

  template <class E>
  BOOST_CONSTEXPR bool operator>(const unexpected_type<E>& x, const unexpected_type<E>& y)
  {
    return (y < x);
  }

  template <class E>
  BOOST_CONSTEXPR bool operator<=(const unexpected_type<E>& x, const unexpected_type<E>& y)
  {
    return !(y < x);
  }

  template <class E>
  BOOST_CONSTEXPR bool operator>=(const unexpected_type<E>& x, const unexpected_type<E>& y)
  {
    return !(x < y);
  }

  inline BOOST_CONSTEXPR bool operator<(const unexpected_type<exception_ptr>&, const unexpected_type<exception_ptr>&)
  {
    return false;
  }
  inline BOOST_CONSTEXPR bool operator>(const unexpected_type<exception_ptr>&, const unexpected_type<exception_ptr>&)
  {
    return false;
  }
  inline BOOST_CONSTEXPR bool operator<=(const unexpected_type<exception_ptr>& x, const unexpected_type<exception_ptr>& y)
  {
    return x==y;
  }
  inline BOOST_CONSTEXPR bool operator>=(const unexpected_type<exception_ptr>& x, const unexpected_type<exception_ptr>& y)
  {
    return x==y;
  }

#ifdef BOOST_EXPECTED_USE_BOOST_HPP
  inline BOOST_CONSTEXPR bool operator<(const unexpected_type<boost::exception_ptr>& x, const unexpected_type<boost::exception_ptr>& y)
  {
    return false;
  }
  inline BOOST_CONSTEXPR bool operator>(const unexpected_type<boost::exception_ptr>& x, const unexpected_type<boost::exception_ptr>& y)
  {
    return false;
  }
  inline BOOST_CONSTEXPR bool operator<=(const unexpected_type<boost::exception_ptr>& x, const unexpected_type<boost::exception_ptr>& y)
  {
    return x==y;
  }
  inline BOOST_CONSTEXPR bool operator>=(const unexpected_type<boost::exception_ptr>& x, const unexpected_type<boost::exception_ptr>& y)
  {
    return x==y;
  }
#endif

  template <typename E>
  struct is_unexpected : false_type {};
  template <typename E>
  struct is_unexpected<unexpected_type<E>> : true_type {};

  BOOST_FORCEINLINE unexpected_type<exception_ptr> make_unexpected_from_current_exception()
  {
    return unexpected_type<exception_ptr> (current_exception());
  }

}}
} // namespace

#endif // JASEL_EXPERIMENTAL_V3_EXPECTED_UNEXPECTED_HPP

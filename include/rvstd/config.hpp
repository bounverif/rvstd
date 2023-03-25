#ifndef RVSTD_CONFIG_HPP
#define RVSTD_CONFIG_HPP

#include <boost/config.hpp>

// Copied from
// https://github.com/boostorg/json/blob/develop/include/boost/json/detail/config.hpp

#ifndef RVSTD_NODISCARD
#ifdef __has_cpp_attribute
// clang-6 accepts [[nodiscard]] with -std=c++14, but warns about it -pedantic
#if __has_cpp_attribute(nodiscard) && \
  !(defined(__clang__) && (__cplusplus < 201703L))
#define RVSTD_NODISCARD [[nodiscard]]
#else
#define RVSTD_NODISCARD
#endif
#else
#define RVSTD_NODISCARD
#endif
#endif

#ifndef RVSTD_DECL
#define RVSTD_DECL
#endif

#ifndef RVSTD_CLASS_DECL
#define RVSTD_CLASS_DECL
#endif

#endif

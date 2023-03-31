#ifndef RVSTD_TYPE_TRAITS_HPP
#define RVSTD_TYPE_TRAITS_HPP

#include <type_traits>

#include <ratio>

namespace rvstd {

template<typename T>
struct is_ratio : std::false_type {
};

template<intmax_t Num, intmax_t Den>
struct is_ratio<std::ratio<Num, Den>> : std::true_type {
};

}  // namespace rvstd

#endif

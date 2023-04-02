#ifndef RVSTD_TYPES_HPP
#define RVSTD_TYPES_HPP

#include <boost/json.hpp>

#include <string_view>

namespace rvstd {

using i64 = std::int64_t;
using u64 = std::uint64_t;
using f64 = std::double_t;
using string_view = std::string_view;

using string = boost::json::string;
using array = boost::json::array;
using object = boost::json::object;
using json = boost::json::value;
using json_ref = boost::json::value_ref;

}  // namespace rvstd

#endif

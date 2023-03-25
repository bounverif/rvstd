#ifndef RVSTD_TYPES_PRIMITIVE_TYPE_HPP
#define RVSTD_TYPES_PRIMITIVE_TYPE_HPP

#include <boost/chrono/duration.hpp>
#include <boost/json.hpp>
#include <string>
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

using time_domain = std::int64_t;
using time_period = boost::micro;
using duration = boost::chrono::duration<time_domain, time_period>;

}  // namespace rvstd

#endif

#ifndef RVSTD_BOOST_JSON_EXT_HPP
#define RVSTD_BOOST_JSON_EXT_HPP

#include "rvstd/timestamp.hpp"

#include <boost/json.hpp>

namespace boost {
namespace json {

auto merge_patch(value& target, value const& patch) -> value&;

}  // namespace json
}  // namespace boost

namespace rvstd {

// get_time specializations for boost::json
template<>
auto get_time(boost::json::value jv) -> timestamp;
template<>
auto get_time(boost::json::object jo) -> timestamp;

}  // namespace rvstd

#endif

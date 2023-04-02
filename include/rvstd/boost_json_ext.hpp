#ifndef RVSTD_BOOST_JSON_EXT_HPP
#define RVSTD_BOOST_JSON_EXT_HPP

#include <boost/json.hpp>

namespace boost {
namespace json {

auto merge_patch(value& target, value const& patch) -> value&;

}  // namespace json
}  // namespace boost

#endif

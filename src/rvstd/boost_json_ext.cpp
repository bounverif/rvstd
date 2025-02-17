#include "rvstd/boost_json_ext.hpp"

namespace boost {
namespace json {

auto merge_patch(value& target, value const& patch) -> value&
{
  if(patch.kind() == kind::object) {
    if(target.kind() != kind::object) {
      target = object();
    }
    auto& to = target.get_object();
    for(const auto& [k, v] : patch.get_object()) {
      if(v.kind() == kind::null) {
        to.erase(k);
      }
      else if(auto* it = to.if_contains(k); it != nullptr) {
        merge_patch(*it, v);
      }
      else {
        to.emplace(k, v);
      }
    }
  }
  else {
    target = patch;
  }
  return target;
}

}  // namespace json
}  // namespace boost

namespace rvstd {

template<>
auto get_time(boost::json::value jv) -> timestamp
{
  return timestamp(jv.at("time").as_uint64());
}

template<>
auto get_time(boost::json::object jo) -> timestamp
{
  return timestamp(jo.at("time").as_uint64());
}

}  // namespace rvstd

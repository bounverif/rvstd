#include "rvstd/resource.hpp"

#include <boost/container_hash/hash.hpp>

namespace rvstd {

resource::resource(
  resource_type code, relations_type rels, attributes_type data)
    : code_(code), rels_(std::move(rels)), data_(std::move(data))
{
}

auto resource::code() const -> identifier_type
{
  return code_;
}

auto resource::relations() const -> relations_type const&
{
  return rels_;
}

auto resource::attributes() const -> attributes_type const&
{
  return data_;
}

auto hash_value(resource const& src) -> std::size_t
{
  std::size_t seed = 0;

  boost::hash_combine(seed, src.code_);
  boost::hash_combine(seed, src.rels_);
  boost::hash_combine(seed, src.data_);

  return seed;
}

// Comparison operators
bool operator==(resource const& lhs, resource const& rhs) noexcept
{
  return lhs.code_ == rhs.code_ && lhs.rels_ == rhs.rels_ &&
         lhs.data_ == rhs.data_;
}
bool operator!=(resource const& lhs, resource const& rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace rvstd

auto std::hash<::rvstd::resource>::operator()(
  ::rvstd::resource const& obj) const noexcept -> size_t
{
  return ::boost::hash<::rvstd::resource>{}(obj);
}

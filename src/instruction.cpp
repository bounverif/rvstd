#include "rvstd/instruction.hpp"

#include <boost/container_hash/hash_fwd.hpp>

namespace rvstd {

auto instruction::code() const -> unique_identifier
{
  return code_;
}

auto instruction::arguments() const -> arguments_type const&
{
  return args_;
}

auto instruction::attributes() const -> attributes_type const&
{
  return data_;
}

}  // namespace rvstd

namespace std {

auto std::hash<::rvstd::instruction>::operator()(
  ::rvstd::instruction const& obj) const noexcept -> size_t
{
  auto seed = std::hash<::rvstd::instruction::instruction_type>{}(obj.code());
  boost::hash_combine(seed, obj.arguments().size());
  for(auto const id : obj.arguments()) {
    boost::hash_combine(
      seed, hash<::rvstd::instruction::identifier_type>{}(id));
  }
  boost::hash_combine(
    seed, std::hash<::rvstd::instruction::attributes_type>{}(obj.attributes()));
  return seed;
}

}  // namespace std

#include "rytest/instruction.hpp"

#include <boost/functional/hash.hpp>

namespace rvstd {

instruction::instruction(
  instruction_type code, arguments_type args, attributes_type data)
    : code_(code), args_(std::move(args)), data_(std::move(data))
{
}

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

// Comparison operators
bool operator==(instruction const& lhs, instruction const& rhs) noexcept
{
  return lhs.code() == rhs.code() && lhs.arguments() == rhs.arguments() &&
         lhs.attributes() == rhs.attributes();
}
bool operator!=(instruction const& lhs, instruction const& rhs) noexcept
{
  return !(lhs == rhs);
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

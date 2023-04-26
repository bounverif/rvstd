#ifndef RVSTD_UNIQUE_IDENTIFIER_HPP
#define RVSTD_UNIQUE_IDENTIFIER_HPP

#include "rvstd/config.hpp"
#include "rvstd/types.hpp"

#include <boost/uuid/uuid.hpp>

namespace rvstd {

struct unique_identifier {
  using type = unique_identifier;
  using value_type = boost::uuids::uuid;

  unique_identifier();
  unique_identifier(string_view name);
  unique_identifier(value_type value);

  RVSTD_NODISCARD
  bool empty() const noexcept;

  RVSTD_NODISCARD
  auto value() const noexcept -> value_type;

  RVSTD_NODISCARD
  auto to_string() const -> string;

  // unique identifier from string
  static auto from_string(string_view str) -> unique_identifier;

  // relations
  friend bool operator<(
    unique_identifier const& lhs, unique_identifier const& rhs) noexcept;
  friend bool operator>(
    unique_identifier const& lhs, unique_identifier const& rhs) noexcept;
  friend bool operator<=(
    unique_identifier const& lhs, unique_identifier const& rhs) noexcept;
  friend bool operator>=(
    unique_identifier const& lhs, unique_identifier const& rhs) noexcept;
  friend bool operator==(
    unique_identifier const& lhs, unique_identifier const& rhs) noexcept;
  friend bool operator!=(
    unique_identifier const& lhs, unique_identifier const& rhs) noexcept;

  // hash
  friend auto hash_value(unique_identifier const& obj) -> std::size_t;

 private:
  value_type value_;
};

auto nil_identifier() -> unique_identifier;

}  // namespace rvstd

template<>
struct std::hash<rvstd::unique_identifier> {
  std::size_t operator()(::rvstd::unique_identifier const& obj) const noexcept;
};

#endif

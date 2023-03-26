#ifndef RVSTD_UNIQUE_IDENTIFIER_HPP
#define RVSTD_UNIQUE_IDENTIFIER_HPP

#include "rvstd/config.hpp"
#include "rvstd/types.hpp"

#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>

namespace rvstd {

struct unique_identifier {
  using type = unique_identifier;
  using value_type = boost::uuids::uuid;

  unique_identifier();
  unique_identifier(string_view name);
  unique_identifier(value_type value);

  RVSTD_NODISCARD
  auto value() const noexcept -> value_type;

  RVSTD_NODISCARD
  auto to_string() const -> string;

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

 private:
  value_type value_;
};

}  // namespace rvstd

template<>
struct std::hash<::boost::uuids::uuid> {
  std::size_t operator()(::boost::uuids::uuid const& obj) const noexcept;
};
template<>
struct std::hash<rvstd::unique_identifier> {
  std::size_t operator()(::rvstd::unique_identifier const& obj) const noexcept;
};

#endif

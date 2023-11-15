#ifndef RVSTD_RESOURCE_HPP
#define RVSTD_RESOURCE_HPP

#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

#include <cstddef>
#include <functional>
#include <map>

namespace rvstd {

struct resource {
  using resource_type = unique_identifier;
  using identifier_type = unique_identifier;
  using relation_type = std::vector<identifier_type>;
  using relations_type = std::unordered_map<unique_identifier, relation_type>;
  using attributes_type = json_value;
  using type = resource;

  resource(
    resource_type code, relations_type rels, attributes_type data = nullptr);

  RVSTD_NODISCARD
  auto code() const -> resource_type;

  RVSTD_NODISCARD
  auto relations() const -> relations_type const&;

  RVSTD_NODISCARD
  auto attributes() const -> attributes_type const&;

  // relations
  friend bool operator==(resource const& lhs, resource const& rhs) noexcept;
  friend bool operator!=(resource const& lhs, resource const& rhs) noexcept;

  // hash
  friend auto hash_value(resource const& src) -> std::size_t;

 private:
  resource_type code_;
  relations_type rels_;
  attributes_type data_;
};

}  // namespace rvstd

namespace std {

template<>
struct hash<rvstd::resource> {
  std::size_t operator()(rvstd::resource const& obj) const noexcept;
};

template<>
struct equal_to<rvstd::resource> {
  bool operator()(
    ::rvstd::resource const& lhs, ::rvstd::resource const& rhs) const noexcept;
};

}  // namespace std

#endif

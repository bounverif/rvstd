#ifndef RVSTD_CONTEXT_HPP
#define RVSTD_CONTEXT_HPP

#include "rvstd/resource.hpp"
#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

#include <boost/container/flat_map.hpp>

namespace rvstd {

/**
 * This is a container adapter
 */
struct unique_context {
  using resource_type = unique_identifier;
  using resource_identifier = unique_identifier;
  using size_type = std::size_t;

  using container_type =
    boost::container::flat_map<resource_identifier, resource>;

  using iterator = container_type::const_iterator;
  using const_iterator = container_type::const_iterator;

  using type = unique_context;

  unique_context();
  // explicit unique_context(options opts = options());
  // explicit unique_context(string_view name, options opts = options());

  // iterators
  RVSTD_NODISCARD
  auto begin() const noexcept -> const_iterator;

  RVSTD_NODISCARD
  auto end() const noexcept -> const_iterator;

  RVSTD_NODISCARD
  auto cbegin() const noexcept -> const_iterator;

  RVSTD_NODISCARD
  auto cend() const noexcept -> const_iterator;

  // capacity
  RVSTD_NODISCARD
  bool empty() const noexcept;

  RVSTD_NODISCARD
  auto size() const noexcept -> size_type;

  // modifiers
  auto emplace(resource const& src) -> resource_identifier;
  auto emplace(resource&& src) -> resource_identifier;
  auto emplace(resource_identifier key, resource const& src)
    -> resource_identifier;
  auto emplace(resource_identifier key, resource&& src) -> resource_identifier;
  auto emplace(string_view name, resource const& src) -> resource_identifier;
  auto emplace(string_view name, resource&& src) -> resource_identifier;

  // lookup
  RVSTD_NODISCARD
  auto find(resource_identifier key) const -> const_iterator;

  RVSTD_NODISCARD
  auto lookup(string_view key) const -> resource_identifier;
  RVSTD_NODISCARD
  auto lookup(resource const& src) const -> resource_identifier;

 private:
  boost::container::flat_map<size_type, resource_identifier> hashes_;
  boost::container::flat_map<resource_identifier, resource> table_;
};

}  // namespace rvstd

#endif

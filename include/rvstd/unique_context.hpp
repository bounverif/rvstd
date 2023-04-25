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
  using resource_type = resource::resource_type;
  using resource_identifier = resource::identifier_type;
  using resource_relations_type = resource::relations_type;
  using resource_attributes_type = resource::attributes_type;

  using table_type = boost::container::flat_map<resource_identifier, resource>;

  using iterator = table_type::const_iterator;
  using const_iterator = table_type::const_iterator;

  using size_type = std::size_t;

  using type = unique_context;

  unique_context();
  // explicit unique_context(options opts = options());
  // explicit unique_context(string_view name, options opts = options());

  RVSTD_NODISCARD
  auto begin() const noexcept -> const_iterator;

  RVSTD_NODISCARD
  auto end() const noexcept -> const_iterator;

  RVSTD_NODISCARD
  auto size() const noexcept -> size_type;

  RVSTD_NODISCARD
  bool empty() const noexcept;

  RVSTD_NODISCARD
  auto find(resource_identifier key) const -> const_iterator;

  RVSTD_NODISCARD
  auto find(string_view key) const -> const_iterator;

  auto emplace(resource_identifier key, resource const& src)
    -> resource_identifier;
  auto emplace(resource_identifier key, resource&& src) -> resource_identifier;

 private:
  boost::container::flat_map<string, resource_identifier> aliases_;
  boost::container::flat_map<size_type, resource_identifier> hashes_;
  boost::container::flat_map<resource_identifier, resource> table_;
};

}  // namespace rvstd

#endif

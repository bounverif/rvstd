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
  using identifier_type = unique_identifier;
  using resource_type = resource;
  using table_type = boost::container::flat_map<identifier_type, resource_type>;

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
  auto find(identifier_type key) const -> const_iterator;

  RVSTD_NODISCARD
  auto find(string_view key) const -> const_iterator;

  auto emplace(identifier_type key, resource_type const& src)
    -> std::pair<const_iterator, bool>;
  auto emplace(identifier_type key, resource_type&& src)
    -> std::pair<const_iterator, bool>;

  // template<
  //   typename... Args,
  //   typename Enable =
  //     typename std::enable_if_t<std::is_constructible_v<resource, Args...>>>
  // auto emplace(identifier_type key, Args&&... args)
  //   -> std::pair<const_iterator, bool>;

  // template<typename... Args>
  // auto emplace(identifier_type key, Args&&... args)
  //   -> std::pair<const_iterator, bool>;

 private:
  boost::container::flat_map<string, identifier_type> aliases_;
  boost::container::flat_map<size_type, identifier_type> hashes_;
  boost::container::flat_map<identifier_type, resource_type> table_;
};

}  // namespace rvstd

#endif

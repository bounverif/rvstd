#ifndef RVSTD_CONTEXT_HPP
#define RVSTD_CONTEXT_HPP

#include "rvstd/config.hpp"
#include "rvstd/resource.hpp"
#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

#include <type_traits>

namespace rvstd {

struct context {
  using key_type = unique_identifier;
  using mapped_type = resource;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = std::less<key_type>;

  using container_type = std::map<key_type, mapped_type>;
  using reference = container_type::reference;
  using const_reference = container_type::const_reference;
  using iterator = container_type::const_iterator;
  using const_iterator = container_type::const_iterator;

  using type = context;

  static_assert(
    std::is_trivially_copyable<const_iterator>::value, "Trivially copyable");

  context();

  // iterators
  RVSTD_NODISCARD
  auto begin() noexcept -> iterator;
  RVSTD_NODISCARD
  auto end() noexcept -> iterator;
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
  RVSTD_NODISCARD
  auto max_size() const noexcept -> size_type;

  // modifiers
  void clear() noexcept;
  auto emplace(resource const& src) -> unique_identifier;
  auto emplace(resource&& src) -> unique_identifier;
  auto emplace(unique_identifier key, resource const& src) -> unique_identifier;
  auto emplace(unique_identifier key, resource&& src) -> unique_identifier;
  auto emplace(string_view name, resource const& src) -> unique_identifier;
  auto emplace(string_view name, resource&& src) -> unique_identifier;
  auto erase(const_iterator pos) -> iterator;
  auto erase(const_iterator first, const_iterator last) -> iterator;
  bool erase(unique_identifier key);
  bool erase(string_view key);

  // lookup
  RVSTD_NODISCARD auto find(unique_identifier key) const -> const_iterator;
  RVSTD_NODISCARD
  auto lookup(string_view key) const -> unique_identifier;
  RVSTD_NODISCARD
  auto lookup(resource const& src) const -> unique_identifier;
  RVSTD_NODISCARD
  bool contains(unique_identifier key) const;
  RVSTD_NODISCARD
  bool contains(string_view key) const;
  RVSTD_NODISCARD
  bool contains(resource const& src) const;

 private:
  std::map<size_type, unique_identifier> hashes_;
  std::map<unique_identifier, resource> table_;
};

}  // namespace rvstd

#endif

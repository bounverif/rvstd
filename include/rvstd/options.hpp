#ifndef RVSTD_OPTIONS_HPP
#define RVSTD_OPTIONS_HPP

#include "rvstd/config.hpp"
#include "rvstd/types.hpp"

#include <boost/json/object.hpp>
#include <boost/json/value.hpp>

#include <filesystem>
#include <system_error>

namespace rvstd {

struct options {
  // types
  using key_type = boost::json::string_view;
  using mapped_type = boost::json::value;
  using value_type =
    std::pair<boost::json::string_view, boost::json::value_ref>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = value_type const&;
  using pointer = mapped_type*;
  using const_pointer = mapped_type const*;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using type = options;

  ~options();
  options(options const& opts);
  options(options&& opts) noexcept = delete;
  auto operator=(options const& opts) -> options&;
  auto operator=(options&& opts) noexcept -> options& = delete;

  options();
  options(string_view name, size_type min_capacity = 0);
  options(std::initializer_list<value_type> il, size_type min_capacity = 0);

  // element access
  RVSTD_NODISCARD
  auto name() const -> string_view;
  RVSTD_NODISCARD
  auto data() const noexcept -> mapped_type const&;
  RVSTD_NODISCARD
  auto operator[](key_type key) const -> mapped_type const&;
  RVSTD_NODISCARD
  auto at(key_type path) const -> mapped_type const&;
  RVSTD_NODISCARD
  auto find(key_type key) const noexcept -> const_pointer;
  RVSTD_NODISCARD
  auto find_at(key_type path, std::error_code& ec) const noexcept
    -> const_pointer;

  // capacity
  RVSTD_NODISCARD
  bool empty() const noexcept;
  RVSTD_NODISCARD
  auto size() const noexcept -> size_type;
  RVSTD_NODISCARD
  auto max_size() const noexcept -> size_type;
  RVSTD_NODISCARD
  auto capacity() const noexcept -> size_type;
  void reserve(size_type new_capacity);

  // modifiers
  RVSTD_NODISCARD
  auto name(string_view name) -> type&;
  auto set(string_view key, mapped_type const& value) -> type&;
  auto set_at(string_view path, mapped_type const& value) -> type&;
  auto load(string_view filepath) -> type&;
  auto load(std::filesystem::path filepath) -> type&;
  auto load_at(string_view path, std::filesystem::path filepath) -> type&;
  auto loads(string_view str) -> type&;
  auto loads_at(string_view path, string_view str) -> type&;
  auto merge(options const& value) -> type&;
  auto merge_at(string_view path, options const& value) -> type&;

  void clear() noexcept;

  // value modifiers
  auto update(string_view path, mapped_type const& value) -> const_iterator;
  auto remove(string_view path) -> const_iterator;

  friend bool operator==(type const& lhs, type const& rhs) noexcept;
  friend bool operator!=(type const& lhs, type const& rhs) noexcept;

 private:
  boost::json::string path_;  // virtual path
  boost::json::string name_;  // virtual path
  boost::json::array dirs_;
  boost::json::value data_;
};

}  // namespace rvstd

#endif

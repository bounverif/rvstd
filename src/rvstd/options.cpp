#include "rvstd/options.hpp"

#include "rvstd/boost_json_ext.hpp"

#include <boost/json/system_error.hpp>

namespace rvstd {

options::~options() = default;
options::options(options const& opts) = default;
auto options::operator=(options const& opts) -> options& = default;
options::options() : data_(boost::json::object{}){};
options::options(string_view name, size_type min_capacity)
    : name_(name), data_(boost::json::object(min_capacity))
{
}
options::options(std::initializer_list<value_type> il, size_type min_capacity)
    : data_(boost::json::object(il, min_capacity))
{
}

auto options::at(key_type key) const -> mapped_type const&
{
  return data_.at_pointer(key);
}

auto options::find(key_type key, std::error_code& ec) const noexcept
  -> const_pointer
{
  return data_.find_pointer(key, ec);
}

RVSTD_NODISCARD
bool options::empty() const noexcept
{
  return data_.as_object().empty();
}

RVSTD_NODISCARD
auto options::size() const noexcept -> size_type
{
  return data_.as_object().size();
}

RVSTD_NODISCARD
auto options::max_size() const noexcept -> size_type
{
  return data_.as_object().max_size();
}

RVSTD_NODISCARD
auto options::capacity() const noexcept -> size_type
{
  return data_.as_object().capacity();
}

void options::reserve(size_type new_capacity)
{
  data_.as_object().reserve(new_capacity);
}

// modifiers
auto options::clear() noexcept -> void
{
  data_.as_object().clear();
}

auto options::set(string_view path, mapped_type const& value) -> type&
{
  data_.set_at_pointer(path, value);
  return *this;
}

auto options::merge(mapped_type const& value) -> type&
{
  boost::json::merge_patch(data_, value);
  return *this;
}

bool operator==(options const& lhs, options const& rhs) noexcept
{
  return lhs.data_ == rhs.data_;
}
bool operator!=(options const& lhs, options const& rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace rvstd

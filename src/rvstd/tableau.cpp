#include "rvstd/tableau.hpp"

#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

namespace rvstd {

tableau::tableau() = default;

auto tableau::begin() noexcept -> iterator
{
  return data_.begin();
}
auto tableau::end() noexcept -> iterator
{
  return data_.end();
}
auto tableau::begin() const noexcept -> const_iterator
{
  return data_.begin();
}
auto tableau::end() const noexcept -> const_iterator
{
  return data_.end();
}
auto tableau::cbegin() const noexcept -> const_iterator
{
  return data_.cbegin();
}
auto tableau::cend() const noexcept -> const_iterator
{
  return data_.cend();
}

// capacity
bool tableau::empty() const noexcept
{
  return data_.empty();
}
auto tableau::size() const noexcept -> size_type
{
  return data_.size();
}
auto tableau::max_size() const noexcept -> size_type
{
  return data_.max_size();
}

// modifiers
void tableau::clear() noexcept
{
  return data_.clear();
}

// lookup
auto tableau::find(unique_identifier key) const -> const_iterator
{
  return data_.find(key);
}

auto tableau::lookup(string_view key) const -> unique_identifier
{
  if(auto const it = data_.find(unique_identifier(key)); it != data_.end()) {
    return it->first;
  }
  return unique_identifier::nil();
}

auto tableau::lookup(resource const& src) const -> unique_identifier
{
  const auto h = std::hash<resource>{}(src);
  if(auto const it = hashes_.find(h); it != hashes_.end()) {
    return it->second;
  }
  return unique_identifier::nil();
}

auto tableau::emplace(resource const& src) -> unique_identifier
{
  return emplace(unique_identifier(), src);
}

auto tableau::emplace(resource&& src) -> unique_identifier
{
  return emplace(unique_identifier(), std::move(src));
}

auto tableau::emplace(unique_identifier key, const resource& src)
  -> unique_identifier
{
  if(key == unique_identifier::nil()) {
    return key;
  }

  const auto h = std::hash<resource>{}(src);

  if(const auto it = hashes_.find(h);
     it != hashes_.end() && it->second != key) {
    return unique_identifier::nil();
  }

  if(const auto [_, success] = data_.emplace(key, src); success) {
    hashes_.emplace(h, key);
    return key;
  }

  return unique_identifier::nil();
}

auto tableau::emplace(unique_identifier key, resource&& src)
  -> unique_identifier
{
  if(key == unique_identifier::nil()) {
    return key;
  }

  const auto h = std::hash<resource>{}(src);

  if(const auto it = hashes_.find(h);
     it != hashes_.end() && it->second != key) {
    return unique_identifier::nil();
  }

  if(const auto [_, success] = data_.emplace(key, std::move(src)); success) {
    hashes_.emplace(h, key);
    return key;
  }
  return unique_identifier::nil();
}

auto tableau::emplace(string_view name, resource const& src)
  -> unique_identifier
{
  return emplace(unique_identifier(name), src);
}

auto tableau::emplace(string_view name, resource&& src) -> unique_identifier
{
  return emplace(unique_identifier(name), std::move(src));
}

auto tableau::erase(const_iterator pos) -> iterator
{
  const auto h = std::hash<resource>{}(pos->second);
  hashes_.erase(h);
  return data_.erase(pos);
}

auto tableau::erase(const_iterator first, const_iterator last) -> iterator
{
  for(auto it = first; it != last; ++it) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
  }
  return data_.erase(first, last);
}

bool tableau::erase(unique_identifier key)
{
  if(const auto it = data_.find(key); it != data_.end()) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
    data_.erase(it);
    return true;
  }
  return false;
}

bool tableau::erase(string_view key)
{
  return this->erase(unique_identifier(key));
}

bool tableau::contains(unique_identifier key) const
{
  return data_.find(key) != data_.end();
}

bool tableau::contains(string_view key) const
{
  return data_.find(unique_identifier(key)) != data_.end();
}

bool tableau::contains(resource const& src) const
{
  return lookup(src) != unique_identifier::nil();
}

}  // namespace rvstd

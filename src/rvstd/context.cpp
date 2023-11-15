#include "rvstd/context.hpp"

#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

namespace rvstd {

context::context() = default;

auto context::begin() noexcept -> iterator
{
  return table_.begin();
}
auto context::end() noexcept -> iterator
{
  return table_.end();
}
auto context::begin() const noexcept -> const_iterator
{
  return table_.begin();
}
auto context::end() const noexcept -> const_iterator
{
  return table_.end();
}
auto context::cbegin() const noexcept -> const_iterator
{
  return table_.cbegin();
}
auto context::cend() const noexcept -> const_iterator
{
  return table_.cend();
}

// capacity
bool context::empty() const noexcept
{
  return table_.empty();
}
auto context::size() const noexcept -> size_type
{
  return table_.size();
}
auto context::max_size() const noexcept -> size_type
{
  return table_.max_size();
}

// modifiers
void context::clear() noexcept
{
  return table_.clear();
}

// lookup
auto context::find(unique_identifier key) const -> const_iterator
{
  return table_.find(key);
}

auto context::lookup(string_view key) const -> unique_identifier
{
  if(auto const it = table_.find(unique_identifier(key)); it != table_.end()) {
    return it->first;
  }
  return unique_identifier::nil();
}

auto context::lookup(resource const& src) const -> unique_identifier
{
  const auto h = std::hash<resource>{}(src);
  if(auto const it = hashes_.find(h); it != hashes_.end()) {
    return it->second;
  }
  return unique_identifier::nil();
}

auto context::emplace(resource const& src) -> unique_identifier
{
  return emplace(unique_identifier(), src);
}

auto context::emplace(resource&& src) -> unique_identifier
{
  return emplace(unique_identifier(), std::move(src));
}

auto context::emplace(unique_identifier key, const resource& src)
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

  if(const auto [_, success] = table_.emplace(key, src); success) {
    hashes_.emplace(h, key);
    return key;
  }

  return unique_identifier::nil();
}

auto context::emplace(unique_identifier key, resource&& src)
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

  if(const auto [_, success] = table_.emplace(key, std::move(src)); success) {
    hashes_.emplace(h, key);
    return key;
  }
  return unique_identifier::nil();
}

auto context::emplace(string_view name, resource const& src)
  -> unique_identifier
{
  return emplace(unique_identifier(name), src);
}

auto context::emplace(string_view name, resource&& src) -> unique_identifier
{
  return emplace(unique_identifier(name), std::move(src));
}

auto context::erase(const_iterator pos) -> iterator
{
  const auto h = std::hash<resource>{}(pos->second);
  hashes_.erase(h);
  return table_.erase(pos);
}

auto context::erase(const_iterator first, const_iterator last) -> iterator
{
  for(auto it = first; it != last; ++it) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
  }
  return table_.erase(first, last);
}

bool context::erase(unique_identifier key)
{
  if(const auto it = table_.find(key); it != table_.end()) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
    table_.erase(it);
    return true;
  }
  return false;
}

bool context::erase(string_view key)
{
  return this->erase(unique_identifier(key));
}

bool context::contains(unique_identifier key) const
{
  return table_.find(key) != table_.end();
}

bool context::contains(string_view key) const
{
  return table_.find(unique_identifier(key)) != table_.end();
}

bool context::contains(resource const& src) const
{
  return lookup(src) != unique_identifier::nil();
}

}  // namespace rvstd

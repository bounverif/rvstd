#include "rvstd/unique_hashtable.hpp"

#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

namespace rvstd {

unique_hashtable::unique_hashtable() = default;

auto unique_hashtable::begin() noexcept -> iterator
{
  return table_.begin();
}
auto unique_hashtable::end() noexcept -> iterator
{
  return table_.end();
}
auto unique_hashtable::begin() const noexcept -> const_iterator
{
  return table_.begin();
}
auto unique_hashtable::end() const noexcept -> const_iterator
{
  return table_.end();
}
auto unique_hashtable::cbegin() const noexcept -> const_iterator
{
  return table_.cbegin();
}
auto unique_hashtable::cend() const noexcept -> const_iterator
{
  return table_.cend();
}

// capacity
bool unique_hashtable::empty() const noexcept
{
  return table_.empty();
}
auto unique_hashtable::size() const noexcept -> size_type
{
  return table_.size();
}
auto unique_hashtable::max_size() const noexcept -> size_type
{
  return table_.max_size();
}

// modifiers
void unique_hashtable::clear() noexcept
{
  return table_.clear();
}

// lookup
auto unique_hashtable::find(unique_identifier key) const -> const_iterator
{
  return table_.find(key);
}

auto unique_hashtable::lookup(string_view key) const -> unique_identifier
{
  if(auto const it = table_.find(unique_identifier(key)); it != table_.end()) {
    return it->first;
  }
  return unique_identifier::nil();
}

auto unique_hashtable::lookup(resource const& src) const -> unique_identifier
{
  const auto h = std::hash<resource>{}(src);
  if(auto const it = hashes_.find(h); it != hashes_.end()) {
    return it->second;
  }
  return unique_identifier::nil();
}

auto unique_hashtable::emplace(resource const& src) -> unique_identifier
{
  return emplace(unique_identifier(), src);
}

auto unique_hashtable::emplace(resource&& src) -> unique_identifier
{
  return emplace(unique_identifier(), std::move(src));
}

auto unique_hashtable::emplace(unique_identifier key, const resource& src)
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

auto unique_hashtable::emplace(unique_identifier key, resource&& src)
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

auto unique_hashtable::emplace(string_view name, resource const& src)
  -> unique_identifier
{
  return emplace(unique_identifier(name), src);
}

auto unique_hashtable::emplace(string_view name, resource&& src)
  -> unique_identifier
{
  return emplace(unique_identifier(name), std::move(src));
}

auto unique_hashtable::erase(const_iterator pos) -> iterator
{
  const auto h = std::hash<resource>{}(pos->second);
  hashes_.erase(h);
  return table_.erase(pos);
}

auto unique_hashtable::erase(const_iterator first, const_iterator last)
  -> iterator
{
  for(auto it = first; it != last; ++it) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
  }
  return table_.erase(first, last);
}

bool unique_hashtable::erase(unique_identifier key)
{
  if(const auto it = table_.find(key); it != table_.end()) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
    table_.erase(it);
    return true;
  }
  return false;
}

bool unique_hashtable::erase(string_view key)
{
  return this->erase(unique_identifier(key));
}

bool unique_hashtable::contains(unique_identifier key) const
{
  return table_.find(key) != table_.end();
}

bool unique_hashtable::contains(string_view key) const
{
  return table_.find(unique_identifier(key)) != table_.end();
}

bool unique_hashtable::contains(resource const& src) const
{
  return lookup(src) != unique_identifier::nil();
}

}  // namespace rvstd

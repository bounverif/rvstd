#include "rvstd/unique_context.hpp"

#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

namespace rvstd {

unique_context::unique_context() = default;

auto unique_context::begin() noexcept -> iterator
{
  return table_.begin();
}
auto unique_context::end() noexcept -> iterator
{
  return table_.end();
}
auto unique_context::begin() const noexcept -> const_iterator
{
  return table_.begin();
}
auto unique_context::end() const noexcept -> const_iterator
{
  return table_.end();
}
auto unique_context::cbegin() const noexcept -> const_iterator
{
  return table_.cbegin();
}
auto unique_context::cend() const noexcept -> const_iterator
{
  return table_.cend();
}

// capacity
bool unique_context::empty() const noexcept
{
  return table_.empty();
}
auto unique_context::size() const noexcept -> size_type
{
  return table_.size();
}
auto unique_context::max_size() const noexcept -> size_type
{
  return table_.max_size();
}

// modifiers
void unique_context::clear() noexcept
{
  return table_.clear();
}

// lookup
auto unique_context::find(unique_identifier key) const -> const_iterator
{
  return table_.find(key);
}

auto unique_context::lookup(string_view key) const -> unique_identifier
{
  if(auto const it = table_.find(unique_identifier(key)); it != table_.end()) {
    return it->first;
  }
  return nil_identifier();
}

auto unique_context::lookup(resource const& src) const -> unique_identifier
{
  const auto h = std::hash<resource>{}(src);
  if(auto const it = hashes_.find(h); it != hashes_.end()) {
    return it->second;
  }
  return nil_identifier();
}

auto unique_context::emplace(resource const& src) -> unique_identifier
{
  return emplace(unique_identifier(), src);
}

auto unique_context::emplace(resource&& src) -> unique_identifier
{
  return emplace(unique_identifier(), std::move(src));
}

auto unique_context::emplace(unique_identifier key, const resource& src)
  -> unique_identifier
{
  if(key == nil_identifier()) {
    return nil_identifier();
  }

  const auto h = std::hash<resource>{}(src);

  if(const auto it = hashes_.find(h);
     it != hashes_.end() && it->second != key) {
    return nil_identifier();
  }

  if(const auto [_, success] = table_.emplace(key, src); success) {
    hashes_.emplace(h, key);
    return key;
  }

  return nil_identifier();
}

auto unique_context::emplace(unique_identifier key, resource&& src)
  -> unique_identifier
{
  if(key == nil_identifier()) {
    return nil_identifier();
  }

  const auto h = std::hash<resource>{}(src);

  if(const auto it = hashes_.find(h);
     it != hashes_.end() && it->second != key) {
    return nil_identifier();
  }

  if(const auto [_, success] = table_.emplace(key, std::move(src)); success) {
    hashes_.emplace(h, key);
    return key;
  }
  return nil_identifier();
}

auto unique_context::emplace(string_view name, resource const& src)
  -> unique_identifier
{
  return emplace(unique_identifier(name), src);
}

auto unique_context::emplace(string_view name, resource&& src)
  -> unique_identifier
{
  return emplace(unique_identifier(name), std::move(src));
}

auto unique_context::erase(const_iterator pos) -> iterator
{
  const auto h = std::hash<resource>{}(pos->second);
  hashes_.erase(h);
  return table_.erase(pos);
}

auto unique_context::erase(const_iterator first, const_iterator last)
  -> iterator
{
  for(auto it = first; it != last; ++it) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
  }
  return table_.erase(first, last);
}

bool unique_context::erase(unique_identifier key)
{
  if(const auto it = table_.find(key); it != table_.end()) {
    const auto h = std::hash<resource>{}(it->second);
    hashes_.erase(h);
    table_.erase(it);
    return true;
  }
  return false;
}

bool unique_context::erase(string_view key)
{
  return this->erase(unique_identifier(key));
}

bool unique_context::contains(unique_identifier key) const
{
  return table_.find(key) != table_.end();
}

bool unique_context::contains(string_view key) const
{
  return table_.find(unique_identifier(key)) != table_.end();
}

bool unique_context::contains(resource const& src) const
{
  return lookup(src) != nil_identifier();
}

}  // namespace rvstd

#include "rvstd/unique_context.hpp"

#include "rvstd/types.hpp"
#include "rvstd/unique_identifier.hpp"

namespace rvstd {

unique_context::unique_context() = default;

auto unique_context::begin() const noexcept -> const_iterator
{
  return this->cbegin();
}

auto unique_context::cbegin() const noexcept -> const_iterator
{
  return table_.cbegin();
}

auto unique_context::end() const noexcept -> const_iterator
{
  return this->cend();
}

auto unique_context::cend() const noexcept -> const_iterator
{
  return table_.cend();
}

auto unique_context::size() const noexcept -> size_type
{
  return table_.size();
}

bool unique_context::empty() const noexcept
{
  return table_.empty();
}

auto unique_context::find(resource_identifier key) const -> const_iterator
{
  return table_.find(key);
}

auto unique_context::lookup(string_view key) const -> resource_identifier
{
  if(auto const it = table_.find(resource_identifier(key));
     it != table_.end()) {
    return it->first;
  }
  return nil_identifier();
}

auto unique_context::lookup(resource const& src) const -> resource_identifier
{
  const auto h = std::hash<resource>{}(src);
  if(auto const it = hashes_.find(h); it != hashes_.end()) {
    return it->second;
  }
  return nil_identifier();
}

auto unique_context::emplace(resource const& src) -> resource_identifier
{
  return emplace(resource_identifier(), src);
}

auto unique_context::emplace(resource&& src) -> resource_identifier
{
  return emplace(resource_identifier(), std::move(src));
}

auto unique_context::emplace(resource_identifier key, const resource& src)
  -> resource_identifier
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

auto unique_context::emplace(resource_identifier key, resource&& src)
  -> resource_identifier
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
  -> resource_identifier
{
  return emplace(resource_identifier(name), src);
}

auto unique_context::emplace(string_view name, resource&& src)
  -> resource_identifier
{
  return emplace(resource_identifier(name), std::move(src));
}

}  // namespace rvstd

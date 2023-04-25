#include "rvstd/unique_context.hpp"

namespace rvstd {

unique_context::unique_context() = default;

auto unique_context::begin() const noexcept -> const_iterator
{
  return table_.begin();
}

auto unique_context::end() const noexcept -> const_iterator
{
  return table_.end();
}

auto unique_context::size() const noexcept -> size_type
{
  return table_.size();
}

bool unique_context::empty() const noexcept
{
  return table_.empty();
}

auto unique_context::find(string_view key) const -> const_iterator
{
  const auto p = aliases_.find(key);
  if(p == aliases_.end()) {
    return end();
  }
  return find(p->second);
}
auto unique_context::find(identifier_type key) const -> const_iterator
{
  return table_.find(key);
}

auto unique_context::emplace(identifier_type key, resource_type const& src)
  -> std::pair<const_iterator, bool>
{
  // const auto src = resource_type(std::forward<Args>(args)...);
  return table_.emplace(key, src);
}

auto unique_context::emplace(identifier_type key, resource_type&& src)
  -> std::pair<const_iterator, bool>
{
  // const auto src = resource_type(std::forward<Args>(args)...);
  return table_.emplace(key, std::move(src));
}

// template<typename... Args>
// auto unique_context::emplace(identifier_type key, Args&&... args)
//   -> std::pair<const_iterator, bool>
// {
//   // const auto src = resource_type(std::forward<Args>(args)...);
//   return table_.emplace(key, args...);
// }

}  // namespace rvstd

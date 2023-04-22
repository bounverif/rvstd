#include "rvstd/unique_identifier.hpp"

#include <boost/functional/hash.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/name_generator_sha1.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace rvstd {
namespace detail {

struct uuids {
  ~uuids() = default;
  uuids(uuids const&) = delete;
  void operator=(uuids const&) = delete;
  uuids(uuids&&) = delete;
  void operator=(uuids&&) = delete;

 public:
  static auto unique_id() -> boost::uuids::uuid;
  static auto unique_id(string_view name) -> boost::uuids::uuid;
  static auto from_uuid(string_view str) -> boost::uuids::uuid;
  static auto to_string(boost::uuids::uuid id) -> string;

 private:
  uuids();
  static auto get() -> uuids&;

 private:
  boost::uuids::random_generator generator_;
  boost::uuids::name_generator_sha1 namegenerator_;
};

uuids::uuids()
    : namegenerator_(boost::uuids::name_generator_sha1(boost::uuids::ns::url()))
{
}

auto uuids::get() -> uuids&
{
  static uuids instance;  // singleton
  return instance;
}

auto uuids::unique_id() -> unique_identifier::value_type
{
  return uuids::get().generator_();
}
auto uuids::unique_id(string_view name) -> boost::uuids::uuid
{
  return uuids::get().namegenerator_(std::string(name));
}
auto uuids::from_uuid(string_view str) -> boost::uuids::uuid
{
  return boost::lexical_cast<boost::uuids::uuid>(str);
}
auto uuids::to_string(boost::uuids::uuid id) -> string
{
  return boost::uuids::to_string(id).c_str();
}
}  // namespace detail

unique_identifier::unique_identifier()
    : unique_identifier(detail::uuids::unique_id())
{
}
unique_identifier::unique_identifier(string_view name)
    : unique_identifier(detail::uuids::unique_id(name))
{
}
unique_identifier::unique_identifier(value_type value) : value_(value) {}

auto unique_identifier::value() const noexcept -> value_type
{
  return value_;
}
auto unique_identifier::to_string() const -> string
{
  return detail::uuids::to_string(value_).c_str();
}
auto unique_identifier::from_string(string_view str) -> unique_identifier
{
  return detail::uuids::from_uuid(str);
}

// relations
bool operator<(
  unique_identifier const& lhs, unique_identifier const& rhs) noexcept
{
  return lhs.value_ < rhs.value_;
}
bool operator>(
  unique_identifier const& lhs, unique_identifier const& rhs) noexcept
{
  return rhs < lhs;
}
bool operator<=(
  unique_identifier const& lhs, unique_identifier const& rhs) noexcept
{
  return !(lhs > rhs);
}
bool operator>=(
  unique_identifier const& lhs, unique_identifier const& rhs) noexcept
{
  return !(lhs < rhs);
}
bool operator==(
  unique_identifier const& lhs, unique_identifier const& rhs) noexcept
{
  return lhs.value_ == rhs.value_;
}
bool operator!=(
  unique_identifier const& lhs, unique_identifier const& rhs) noexcept
{
  return not(lhs == rhs);
}

auto hash_value(unique_identifier const& obj) -> std::size_t
{
  return ::boost::hash<::boost::uuids::uuid>()(obj.value_);
}

}  // namespace rvstd

auto std::hash<::rvstd::unique_identifier>::operator()(
  ::rvstd::unique_identifier const& obj) const noexcept -> std::size_t
{
  return ::boost::hash<::rvstd::unique_identifier>()(obj);
}

// auto std::hash<::boost::uuids::uuid>::operator()(
//   ::boost::uuids::uuid const& obj) const noexcept -> std::size_t
// {
//   return ::boost::hash<::boost::uuids::uuid>()(obj);
// }

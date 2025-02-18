#ifndef RVSTD_PROPERTY_HPP
#define RVSTD_PROPERTY_HPP

namespace rvstd {

struct property {
  property() = default;
  property(property const& prop) = delete;
  property(property&& prop) noexcept = delete;
  auto operator=(property const& prop) -> property& = delete;
  auto operator=(property&& prop) noexcept -> property& = delete;
  ~property() = default;

 public:
  int value;
};

}  // namespace rvstd

#endif

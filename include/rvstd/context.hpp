#ifndef RVSTD_CONTEXT_HPP
#define RVSTD_CONTEXT_HPP

#include "rvstd/tableau.hpp"

namespace rvstd {

struct context {
  context();
  context(context const& ctx) = delete;
  context(context&& ctx) noexcept = delete;
  auto operator=(context const& ctx) -> context& = delete;
  auto operator=(context&& ctx) noexcept -> context& = delete;
  ~context();

 public:
  tableau data;
};

}  // namespace rvstd

#endif

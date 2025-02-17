#ifndef RVSTD_TIMESTAMP_HPP
#define RVSTD_TIMESTAMP_HPP

#include <cstdint>

namespace rvstd {

struct timestamp {
  explicit timestamp(std::int64_t value) : value(value) {}
  std::int64_t value;
};

// Template specialization
template<typename T>
auto get_time(T /*object*/) -> timestamp
{
  return timestamp(0);
}

}  // namespace rvstd

#endif  // RVSTD_TIMESTAMP_HPP

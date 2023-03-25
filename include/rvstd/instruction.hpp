#ifndef RVSTD_INSTRUCTION_HPP
#define RVSTD_INSTRUCTION_HPP

#include "rvstd/config.hpp"
#include "rvstd/unique_identifier.hpp"

#include <boost/json/value.hpp>

#include <utility>

namespace rvstd {

struct instruction {
  using instruction_type = unique_identifier;
  using identifier_type = unique_identifier;
  using arguments_type = std::vector<identifier_type>;
  using attributes_type = boost::json::value;
  using type = instruction;

  instruction(
    instruction_type code, arguments_type args, attributes_type data = nullptr)
      : code_(code), args_(std::move(args)), data_(std::move(data))
  {
  }

  RVSTD_NODISCARD
  auto code() const -> instruction_type;

  RVSTD_NODISCARD
  auto arguments() const -> arguments_type const&;

  RVSTD_NODISCARD
  auto attributes() const -> attributes_type const&;

 private:
  instruction_type code_;
  arguments_type args_;
  attributes_type data_;
};

}  // namespace rvstd

namespace std {

template<>
struct hash<rvstd::instruction> {
  std::size_t operator()(rvstd::instruction const& obj) const noexcept;
};

}  // namespace std

#endif

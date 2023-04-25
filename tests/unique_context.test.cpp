#include "rvstd/unique_context.hpp"

#include "rvstd/unique_identifier.hpp"

#include <catch2/catch_test_macros.hpp>

#include <utility>

TEST_CASE("Unique Context", "core")  // NOLINT
{
  using namespace rvstd;

  SECTION("Default Construction")
  {
    auto ctx = rvstd::unique_context();
    REQUIRE(ctx.empty());
  }

  SECTION("Emplace")
  {
    auto ctx = rvstd::unique_context();
    auto idx = rvstd::unique_identifier("key");
    auto type = rvstd::unique_identifier("type");
    auto rel1 = rvstd::unique_identifier("rel1");
    auto arg1 = rvstd::unique_identifier("arg1");
    auto arg2 = rvstd::unique_identifier("arg2");

    ctx.emplace(idx, resource(type, {{rel1, {arg1, arg2}}}));
    REQUIRE(ctx.empty());
  }
}

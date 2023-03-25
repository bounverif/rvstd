#include "rvstd/unique_identifier.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(  // NOLINT(readability-function-cognitive-complexity)
  "Resource Identifier",
  "core")
{
  using namespace rvstd;

  SECTION("Default Constructor")
  {
    REQUIRE(unique_identifier() != unique_identifier());
    REQUIRE(unique_identifier("bounverif") != unique_identifier("labs"));
    REQUIRE(unique_identifier("bounverif") == unique_identifier("bounverif"));
  }

  SECTION("Relations")
  {
    auto id1 = unique_identifier("bounverif");
    auto id2 = unique_identifier("bounverif");
    auto id3 = unique_identifier("labs");

    REQUIRE(id1 == id2);
    REQUIRE(id1 != id3);
  }

  SECTION("Hashing")
  {
    auto src1 = unique_identifier("bounverif");
    auto src2 = unique_identifier("bounverif");
    auto src3 = unique_identifier("labs");

    REQUIRE(
      std::hash<unique_identifier>{}(src1) ==
      std::hash<unique_identifier>{}(src2));
    REQUIRE(
      std::hash<unique_identifier>{}(src1) !=
      std::hash<unique_identifier>{}(src3));
  }

  SECTION("String conversion")
  {
    auto idx = unique_identifier("bounverif");
    auto str = idx.to_string();
  }
}

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

  SECTION("Null Constructor")
  {
    std::string nil_uuid = "00000000-0000-0000-0000-000000000000";

    REQUIRE(nil_identifier().empty() == true);
    REQUIRE(nil_identifier().to_string() == nil_uuid);
    REQUIRE(nil_identifier() == unique_identifier::from_string(nil_uuid));
    REQUIRE(
      nil_identifier().value() ==
      unique_identifier::from_string(nil_uuid).value());
    REQUIRE(nil_identifier() == nil_identifier());
  }

  SECTION("Construction from UUID String")
  {
    auto idx = unique_identifier("bounverif");
    auto str = idx.to_string();

    REQUIRE(idx == unique_identifier::from_string(str));
  }

  SECTION("String conversion")
  {
    auto idx = unique_identifier("bounverif");
    auto str = idx.to_string();
  }

  SECTION("String conversion (const)")
  {
    const auto idx = unique_identifier("bounverif");
    auto str = idx.to_string();
  }

  SECTION("Equality")
  {
    auto src1 = unique_identifier("bounverif");
    auto src2 = unique_identifier("bounverif");
    auto src3 = unique_identifier("labs");

    REQUIRE(src1 == src2);
    REQUIRE(src1 != src3);
  }

  SECTION("Relations")
  {
    auto src1 = unique_identifier("bounverif");
    auto src2 = unique_identifier("bounverif");
    auto src3 = unique_identifier("labs");

    REQUIRE(!(src1 < src2));
    REQUIRE(!(src1 > src3));

    REQUIRE(src1 < src3);
    REQUIRE(src1 <= src2);
    REQUIRE(src1 <= src3);
    REQUIRE(src1 >= src2);
    REQUIRE(src3 >= src1);
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
}

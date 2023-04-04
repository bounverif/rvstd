#include "rvstd/boost_json_ext.hpp"

#include <boost/json/value.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Boost JSON Merge Patch", "core")  // NOLINT
{
  SECTION("Merge objects")
  {
    auto j1 = boost::json::value{{"a", 1}, {"b", 2}, {"c", 3}};
    auto j2 = boost::json::value{{"b", 4}, {"d", 5}};
    auto j3 = boost::json::value{{"a", 1}, {"b", 4}, {"c", 3}, {"d", 5}};

    boost::json::merge_patch(j1, j2);

    REQUIRE(j1 == j3);
  }

  SECTION("Overwrite non-object with object")
  {
    auto target = boost::json::value{1};
    auto patch = boost::json::value{{"a", 1}};
    auto expected = boost::json::value{{"a", 1}};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }

  SECTION("Overwrite object with non-object")
  {
    auto target = boost::json::value{{"a", 1}};
    auto patch = boost::json::value{1};
    auto expected = boost::json::value{1};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }

  SECTION("Overwrite array with array")
  {
    auto target = boost::json::value{1, 2, 3};
    auto patch = boost::json::value{4, 5, 6};
    auto expected = boost::json::value{4, 5, 6};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }

  SECTION("Erase scalar with null")
  {
    auto target = boost::json::value{1};
    auto patch = boost::json::value{nullptr};
    auto expected = boost::json::value{nullptr};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }

  SECTION("Erase array with null")
  {
    auto target = boost::json::value{1, 2, 3};
    auto patch = boost::json::value{nullptr};
    auto expected = boost::json::value{nullptr};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }

  SECTION("Erase object with null")
  {
    auto target = boost::json::value{{"a", 1}, {"b", 2}};
    auto patch = boost::json::value{nullptr};
    auto expected = boost::json::value{nullptr};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }

  SECTION("RFC 7386 Example")
  {
    auto target = boost::json::value{
      {"title", "Goodbye!"},
      {"author", {{"givenName", "John"}, {"familyName", "Doe"}}},
      {"tags", {"example", "sample"}},
      {"content", "This will be unchanged"}};
    auto patch = boost::json::value{
      {"title", "Hello!"},
      {"author", {{"familyName", nullptr}}},
      {"phoneNumber", "+01-123-456-7890"},
      {"tags", {"example"}}};
    auto expected = boost::json::value{
      {"title", "Hello!"},
      {"author", {{"givenName", "John"}}},
      {"tags", {"example"}},
      {"phoneNumber", "+01-123-456-7890"},
      {"content", "This will be unchanged"}};

    boost::json::merge_patch(target, patch);

    REQUIRE(target == expected);
  }
}

#include "rvstd/boost_json_ext.hpp"

#include <boost/json/value.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Boost JSON Merge Patch", "core")  // NOLINT
{
  SECTION("Merge Patch: Object")
  {
    auto j1 = boost::json::value{{"a", 1}, {"b", 2}, {"c", 3}};
    auto j2 = boost::json::value{{"b", 4}, {"d", 5}};
    auto j3 = boost::json::value{{"a", 1}, {"b", 4}, {"c", 3}, {"d", 5}};

    boost::json::merge_patch(j1, j2);

    REQUIRE(j1 == j3);
  }

  SECTION("RFC 7386 Example")
  {
    auto doc = boost::json::value{{"title", "Goodbye!"}};
    auto patch = boost::json::value{{"title", "Hello!"}};
    auto patched_doc = boost::json::value{{"title", "Hello!"}};

    boost::json::merge_patch(doc, patch);

    REQUIRE(doc == patched_doc);
  }

  SECTION("RFC 7386 Example")
  {
    auto doc = boost::json::value{{"title", "Goodbye!"}};
    auto patch = boost::json::value{{"title", nullptr}};
    auto patched_doc = boost::json::object{};

    boost::json::merge_patch(doc, patch);

    REQUIRE(doc == patched_doc);
  }

  SECTION("RFC 7386 Example")
  {
    auto doc = boost::json::value{
      {"author", {{"givenName", "John"}, {"familyName", "Doe"}}}};
    auto patch = boost::json::value{{"author", {{"familyName", nullptr}}}};
    auto patched_doc = boost::json::value{{"author", {{"givenName", "John"}}}};

    boost::json::merge_patch(doc, patch);

    REQUIRE(doc == patched_doc);
  }

  SECTION("RFC 7386 Example")
  {
    auto doc = boost::json::value{
      {"title", "Goodbye!"},
      {"author", {{"givenName", "John"}, {"familyName", "Doe"}}},
      {"tags", {"example", "sample"}},
      {"content", "This will be unchanged"}};
    auto patch = boost::json::value{
      {"title", "Hello!"},
      {"author", {{"familyName", nullptr}}},
      {"phoneNumber", "+01-123-456-7890"},
      {"tags", {"example"}}};
    auto patched_doc = boost::json::value{
      {"title", "Hello!"},
      {"author", {{"givenName", "John"}}},
      {"tags", {"example"}},
      {"phoneNumber", "+01-123-456-7890"},
      {"content", "This will be unchanged"}};

    boost::json::merge_patch(doc, patch);

    REQUIRE(doc == patched_doc);
  }
}

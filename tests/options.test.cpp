#include "rvstd/options.hpp"

#include <boost/json/value.hpp>
#include <catch2/catch_test_macros.hpp>

#include <utility>

TEST_CASE("Construction", "core")  // NOLINT
{
  SECTION("Default")
  {
    auto config = rvstd::options();
    REQUIRE(config.empty());
  }
  SECTION("Construct from initializer list")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    REQUIRE(opts.size() == 3);
  }
  SECTION("Construct from initializer list")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    REQUIRE(opts.size() == 3);
  }
  SECTION("Copy Constructor")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options(opts1);
    REQUIRE(opts1 == opts2);
  }
  SECTION("Copy Assignment")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options();
    opts2 = opts1;
    REQUIRE(opts1 == opts2);
  }
}

TEST_CASE("Fluent Construction", "core")  // NOLINT
{
  SECTION("Basic Usage")
  {
    auto opts = rvstd::options("config")  //
                  .set_at("/a", 1)
                  .set_at("/b", 2)
                  .set_at("/c", 3);

    REQUIRE(opts.size() == 3);
    REQUIRE(opts.at("/a") == 1);
    REQUIRE(opts.at("/b") == 2);
    REQUIRE(opts.at("/c") == 3);
  }
  SECTION("Nested Objects")
  {
    auto opts = rvstd::options("config")  //
                  .set_at("/a", 1)
                  .set_at("/b", 2)
                  .set_at("/c", 3)
                  .set_at("/d", {{"x", 1}, {"y", 2}, {"z", 3}});

    REQUIRE(opts.size() == 4);
    REQUIRE(opts.at("/a") == 1);
    REQUIRE(opts.at("/b") == 2);
    REQUIRE(opts.at("/c") == 3);
    REQUIRE(opts.at("/d/x") == 1);
    REQUIRE(opts.at("/d/y") == 2);
    REQUIRE(opts.at("/d/z") == 3);
  }
}

TEST_CASE("Element Access")  // NOLINT
{
  SECTION("Operator[]")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts["a"] == 1);
    REQUIRE(opts["b"] == 2);
    REQUIRE(opts["c"] == 3);
  }
  SECTION("Operator[] (const)")
  {
    const auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts["a"] == 1);
    REQUIRE(opts["b"] == 2);
    REQUIRE(opts["c"] == 3);
  }

  SECTION("At")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts.at("/a") == 1);
    REQUIRE(opts.at("/b") == 2);
    REQUIRE(opts.at("/c") == 3);
  }

  SECTION("At (const)")
  {
    const auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts.at("/a") == 1);
    REQUIRE(opts.at("/b") == 2);
    REQUIRE(opts.at("/c") == 3);
  }

  SECTION("Find")
  {
    auto ec = std::error_code{};
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts.find("a") != nullptr);
    REQUIRE(opts.find("b") != nullptr);
    REQUIRE(opts.find("c") != nullptr);
    REQUIRE(opts.find("d") == nullptr);
  }

  SECTION("FindAt")
  {
    auto ec = std::error_code{};
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts.find_at("/a", ec) != nullptr);
    REQUIRE(opts.find_at("/b", ec) != nullptr);
    REQUIRE(opts.find_at("/c", ec) != nullptr);
    REQUIRE(opts.find_at("/d", ec) == nullptr);
  }

  SECTION("Find (const)")
  {
    auto ec = std::error_code{};
    const auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    REQUIRE(opts.find_at("/a", ec) != nullptr);
    REQUIRE(opts.find_at("/b", ec) != nullptr);
    REQUIRE(opts.find_at("/c", ec) != nullptr);
    REQUIRE(opts.find_at("/d", ec) == nullptr);
  }

  SECTION("Nested Access")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};

    opts.set_at("/nested", {{"d", 4}, {"e", 5}, {"f", 6}});

    REQUIRE(opts.at("/nested/d") == 4);
    REQUIRE(opts.at("/nested/e") == 5);
    REQUIRE(opts.at("/nested/f") == 6);
  }
}

TEST_CASE("Capacity")  // NOLINT
{
  SECTION("Empty")
  {
    auto opts = rvstd::options();
    REQUIRE(opts.empty());
  }
  SECTION("Size")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    REQUIRE(opts.size() == 3);
  }
  SECTION("Max Size")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    REQUIRE(opts.capacity() <= opts.max_size());
  }
  SECTION("Reserve")
  {
    auto opts = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    opts.reserve(10);
    REQUIRE(opts.capacity() >= 10);
  }
}

TEST_CASE("Operations", "core")  //  NOLINT
{
  SECTION("Equality")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    REQUIRE(opts1 == opts2);
  }

  SECTION("Non-Equality")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 4}};
    REQUIRE(opts1 != opts2);
  }

  SECTION("Basic Merge")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options{{"d", 4}, {"e", 5}, {"f", 6}};
    auto expected = rvstd::options{
      {"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}, {"f", 6}};

    opts1.merge(opts2);

    REQUIRE(opts1 == expected);
  }

  SECTION("Basic Merge")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options{{"a", 4}, {"b", 5}, {"c", 6}};
    auto expected = rvstd::options{{"a", 4}, {"b", 5}, {"c", 6}};

    opts1.merge(opts2);

    REQUIRE(opts1 == expected);
  }

  SECTION("Basic Merge")
  {
    auto opts1 = rvstd::options{{"a", 1}, {"b", 2}, {"c", 3}};
    auto opts2 = rvstd::options{{"a", 4}, {"b", 5}, {"d", 6}};
    auto expected = rvstd::options{{"a", 4}, {"b", 5}, {"c", 3}, {"d", 6}};

    opts1.merge(opts2);

    REQUIRE(opts1 == expected);
  }
}

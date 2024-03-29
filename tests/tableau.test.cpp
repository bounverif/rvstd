#include "rvstd/tableau.hpp"

#include "rvstd/unique_identifier.hpp"

#include <catch2/catch_test_macros.hpp>

#include <utility>

TEST_CASE("Unique Tableau Construction", "core")  // NOLINT
{
  using namespace rvstd;
  auto ctx = rvstd::tableau();

  SECTION("Default Construction")
  {
    REQUIRE(ctx.empty());
  }
}

TEST_CASE("Unique Tableau Lookup", "core")  // NOLINT
{
  using namespace rvstd;
  auto ctx = rvstd::tableau();

  auto idx = rvstd::unique_identifier("key");
  auto type = rvstd::unique_identifier("type");
  auto rel1 = rvstd::unique_identifier("rel1");
  auto arg1 = rvstd::unique_identifier("arg1");
  auto arg2 = rvstd::unique_identifier("arg2");
  auto arg3 = rvstd::unique_identifier("arg3");
  auto arg4 = rvstd::unique_identifier("arg4");

  auto id1 = ctx.emplace(resource(type, {{rel1, {arg1, arg2}}}));
  auto id2 = ctx.emplace(resource(type, {{rel1, {arg2, arg3}}}));
  auto id3 = ctx.emplace(resource(type, {{rel1, {arg3, arg4}}}));

  SECTION("Default Construction")
  {
    REQUIRE(ctx.size() == 3);
  }

  SECTION("Iterate")
  {
    auto count = 0;
    for(const auto& [id, res] : ctx) {
      count++;
    }
    REQUIRE(count == 3);
  }

  SECTION("Successful Lookup")
  {
    const auto src = resource(type, {{rel1, {arg1, arg2}}});
    REQUIRE(ctx.lookup(src) == id1);
    REQUIRE(ctx.lookup(src) != unique_identifier::nil());
  }

  SECTION("Unsuccessful Lookup")
  {
    const auto src = resource(type, {{rel1, {arg1, arg3}}});
    REQUIRE(ctx.lookup(src) == unique_identifier::nil());
  }

  SECTION("Lookup 2")
  {
    const auto src = resource(type, {{rel1, {arg2, arg3}}});
    REQUIRE(ctx.lookup(src) == id2);
    REQUIRE(ctx.lookup(src) != unique_identifier::nil());
  }

  SECTION("Lookup 3")
  {
    const auto src = resource(type, {{rel1, {arg2, arg3}}});
    REQUIRE(ctx.lookup("nonexistent") == unique_identifier::nil());
  }
}

TEST_CASE("Unique Tableau Emplace", "core")  // NOLINT
{
  using namespace rvstd;
  auto ctx = rvstd::tableau();

  auto idx = rvstd::unique_identifier("key");
  auto type = rvstd::unique_identifier("type");
  auto rel1 = rvstd::unique_identifier("rel1");
  auto arg1 = rvstd::unique_identifier("arg1");
  auto arg2 = rvstd::unique_identifier("arg2");
  auto arg3 = rvstd::unique_identifier("arg3");
  auto arg4 = rvstd::unique_identifier("arg4");

  SECTION("Emplace (rvalue)")
  {
    auto id1 = ctx.emplace(idx, resource(type, {{rel1, {arg1, arg2}}}));

    REQUIRE(id1 != unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
    REQUIRE(ctx.find(id1) != ctx.end());
  }

  SECTION("Emplace (rvalue)")
  {
    auto id1 = ctx.emplace(resource(type, {{rel1, {arg1, arg2}}}));

    REQUIRE(id1 != unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
    REQUIRE(ctx.find(id1) != ctx.end());
  }

  SECTION("Emplace (lvalue)")
  {
    auto res = resource(type, {{rel1, {arg1, arg2}}});
    auto id1 = ctx.emplace(idx, res);

    REQUIRE(id1 != unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
    REQUIRE(ctx.find(id1) != ctx.end());
  }

  SECTION("Emplace (lvalue)")
  {
    auto res = resource(type, {{rel1, {arg1, arg2}}});
    auto id1 = ctx.emplace(res);

    REQUIRE(id1 != unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
    REQUIRE(ctx.find(id1) != ctx.end());
  }

  SECTION("Named emplace (lvalue)")
  {
    auto src = resource(type, {{rel1, {arg1, arg2}}});
    auto id1 = ctx.emplace("resource", src);

    REQUIRE(id1 != unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
    REQUIRE(ctx.find(id1) != ctx.end());
    REQUIRE(ctx.lookup(resource(type, {{rel1, {arg1, arg2}}})) == id1);
    REQUIRE(ctx.lookup("resource") == id1);
  }

  SECTION("Named emplace (rvalue)")
  {
    auto src = resource(type, {{rel1, {arg1, arg2}}});
    auto id1 = ctx.emplace("resource", std::move(src));

    REQUIRE(id1 != unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
    REQUIRE(ctx.find(id1) != ctx.end());
    REQUIRE(ctx.lookup(resource(type, {{rel1, {arg1, arg2}}})) == id1);
    REQUIRE(ctx.lookup("resource") == id1);
  }

  SECTION("Nil Emplace 1")
  {
    auto src = resource(type, {{rel1, {arg1, arg2}}});
    ctx.emplace(unique_identifier::nil(), src);

    REQUIRE(ctx.empty());
  }

  SECTION("Nil Emplace 2")
  {
    auto src = resource(type, {{rel1, {arg1, arg2}}});
    ctx.emplace(unique_identifier::nil(), std::move(src));

    REQUIRE(ctx.empty());
  }

  SECTION("Emplace 1")
  {
    auto src = resource(type, {{rel1, {arg3, arg4}}});
    auto id3 = ctx.emplace(resource(type, {{rel1, {arg3, arg4}}}));
    auto id4 = ctx.emplace("hello", src);

    REQUIRE(id4 != id3);
    REQUIRE(id4 == unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
  }

  SECTION("Emplace 1")
  {
    auto src = resource(type, {{rel1, {arg3, arg4}}});
    auto id3 = ctx.emplace(resource(type, {{rel1, {arg3, arg4}}}));
    auto id4 = ctx.emplace("hello", std::move(src));

    REQUIRE(id4 != id3);
    REQUIRE(id4 == unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
  }

  SECTION("Emplace 2")
  {
    auto src = resource(type, {{rel1, {arg3, arg1}}});
    auto id4 = ctx.emplace("hello", src);

    REQUIRE(id4 != unique_identifier::nil());
    REQUIRE(id4 == unique_identifier("hello"));
    REQUIRE(ctx.size() == 1);
  }

  SECTION("Emplace 2")
  {
    auto src = resource(type, {{rel1, {arg3, arg1}}});
    auto id4 = ctx.emplace("hello", std::move(src));

    REQUIRE(id4 != unique_identifier::nil());
    REQUIRE(id4 == unique_identifier("hello"));
    REQUIRE(ctx.size() == 1);
  }

  SECTION("Emplace 3 (lvalue)")
  {
    auto id4 = unique_identifier("hello");
    auto id5 = unique_identifier("hello");

    auto src = resource(type, {{rel1, {arg3, arg1}}});

    auto id6 = ctx.emplace(id4, src);
    auto id7 = ctx.emplace(id5, src);

    REQUIRE(id6 == id4);
    REQUIRE(id7 == unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
  }

  SECTION("Emplace 3 (rvalue)")
  {
    auto id4 = unique_identifier("hello");
    auto id5 = unique_identifier("hello");

    auto src = resource(type, {{rel1, {arg3, arg1}}});

    auto id6 = ctx.emplace(id4, src);
    auto id7 = ctx.emplace(id5, std::move(src));

    REQUIRE(id6 == id4);
    REQUIRE(id7 == unique_identifier::nil());
    REQUIRE(ctx.size() == 1);
  }
}

#include "rvstd/resource.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(  // NOLINT(readability-function-cognitive-complexity)
  "Resource",
  "core")
{
  using namespace rvstd;

  auto type1 = unique_identifier("type1");
  auto type2 = unique_identifier("type2");

  auto rel1 = unique_identifier("rel1");
  auto rel2 = unique_identifier("rel2");

  auto arg1 = unique_identifier("arg1");
  auto arg2 = unique_identifier("arg2");
  auto arg3 = unique_identifier("arg3");
  auto arg4 = unique_identifier("arg4");

  auto attr1 = boost::json::value(1);
  auto attr2 = boost::json::value("2");
  auto attr3 = boost::json::value(3.0);
  auto attr4 = boost::json::value(true);
  auto attr5 = boost::json::value(false);
  auto attr6 = boost::json::value(nullptr);
  auto attr7 = boost::json::value({1, 2, 3});
  auto attr8 = boost::json::value({{"a", 1}, {"b", 2}, {"c", 3}});

  SECTION("Construction")
  {
    auto const s = resource(type1, {{rel1, {arg1, arg2}}});

    REQUIRE(s.code() == type1);
    REQUIRE(s.relations() == resource::relations_type({{rel1, {arg1, arg2}}}));
    REQUIRE(s.attributes() == nullptr);
  }

  SECTION("Construction with attributes")
  {
    auto const s = resource(type1, {{rel1, {arg1, arg2}}}, attr1);

    REQUIRE(s.code() == type1);
    REQUIRE(s.relations() == resource::relations_type({{rel1, {arg1, arg2}}}));
    REQUIRE(s.attributes() == attr1);
  }

  SECTION("Copy Constructor")
  {
    auto const s = resource(type1, {{rel1, {arg1, arg2}}});

    REQUIRE(resource(s) == s);
  }
  SECTION("Move Constructor")
  {
    auto const s = resource(type1, {{rel1, {arg1, arg2}}});

    REQUIRE(resource(resource(type1, {{rel1, {arg1, arg2}}})) == s);
  }

  SECTION("Copy Assignment")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto s2 = resource(type2, {{rel2, {arg3, arg4}}});
    s2 = s1;

    REQUIRE(s2 == s1);
  }

  SECTION("Move Assignment")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto s2 = resource(type2, {{rel2, {arg3, arg4}}});
    s2 = resource(type1, {{rel1, {arg1, arg2}}});

    REQUIRE(s2 == s1);
  }

  SECTION("Equality")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto const s2 = resource(type1, {{rel1, {arg1, arg2}}});

    REQUIRE(s1 == s2);
  }

  SECTION("Inequality")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto const s2 = resource(type2, {{rel1, {arg1, arg2}}});

    REQUIRE(s1 != s2);
  }
}

TEST_CASE(  // NOLINT(readability-function-cognitive-complexity)
  "Resource Hashing",
  "core")
{
  using namespace rvstd;

  auto type1 = unique_identifier("type1");
  auto type2 = unique_identifier("type2");

  auto rel1 = unique_identifier("rel1");
  auto rel2 = unique_identifier("rel2");

  auto arg1 = unique_identifier("arg1");
  auto arg2 = unique_identifier("arg2");
  auto arg3 = unique_identifier("arg3");
  auto arg4 = unique_identifier("arg4");

  auto attr1 = boost::json::value(1);
  auto attr2 = boost::json::value("2");
  auto attr3 = boost::json::value(3.0);
  auto attr4 = boost::json::value(true);
  auto attr5 = boost::json::value(false);
  auto attr6 = boost::json::value(nullptr);
  auto attr7 = boost::json::value({1, 2, 3});
  auto attr8 = boost::json::value({{"a", 1}, {"b", 2}, {"c", 3}});

  SECTION("Hash 1")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto const s2 = resource(type1, {{rel1, {arg1, arg2}}});

    REQUIRE(std::hash<resource>{}(s1) == std::hash<resource>{}(s2));
  }

  SECTION("Hash 2")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto const s2 = resource(type2, {{rel1, {arg1, arg2}}});

    REQUIRE(std::hash<resource>{}(s1) != std::hash<resource>{}(s2));
  }

  SECTION("Hash 3")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto const s2 = resource(type1, {{rel2, {arg1, arg2}}});

    REQUIRE(std::hash<resource>{}(s1) != std::hash<resource>{}(s2));
  }

  SECTION("Hash 3")
  {
    auto const s1 = resource(type1, {{rel1, {arg1, arg2}}});
    auto const s2 = resource(type1, {{rel1, {arg2, arg1}}});

    REQUIRE(std::hash<resource>{}(s1) != std::hash<resource>{}(s2));
  }

  SECTION("Hash 4")
  {
    auto const s1 =
      resource(type1, {{rel1, {arg1, arg2}}, {rel2, {arg3, arg4}}});
    auto const s2 =
      resource(type1, {{rel2, {arg3, arg4}}, {rel1, {arg1, arg2}}});

    REQUIRE(std::hash<resource>{}(s1) == std::hash<resource>{}(s2));
  }
}

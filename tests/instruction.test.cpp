#include "rvstd/instruction.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE(  // NOLINT(readability-function-cognitive-complexity)
  "Instruction",
  "core")
{
  using namespace rvstd;

  auto type1 = unique_identifier("type1");
  auto type2 = unique_identifier("type2");

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
    auto const inst = instruction(type1, {arg1, arg2});

    REQUIRE(inst.code() == type1);
    REQUIRE(inst.arguments() == std::vector{arg1, arg2});
    REQUIRE(inst.attributes() == nullptr);
  }

  SECTION("Construction with attributes")
  {
    auto const inst = instruction(type1, {arg1, arg2}, attr1);

    REQUIRE(inst.code() == type1);
    REQUIRE(inst.arguments() == std::vector{arg1, arg2});
    REQUIRE(inst.attributes() == attr1);
  }

  SECTION("Copy Constructor")
  {
    auto const inst = instruction(type1, {arg1, arg2});

    REQUIRE(instruction(inst) == inst);
  }
  SECTION("Move Constructor")
  {
    auto const inst = instruction(type1, {arg1, arg2});

    REQUIRE(instruction(instruction(type1, {arg1, arg2})) == inst);
  }

  SECTION("Copy Assignment")
  {
    auto const inst = instruction(type1, {arg1, arg2});
    auto inst2 = instruction(type2, {arg3, arg4});
    inst2 = inst;

    REQUIRE(inst2 == inst);
  }

  SECTION("Move Assignment")
  {
    auto const inst = instruction(type1, {arg1, arg2});
    auto inst2 = instruction(type2, {arg3, arg4});
    inst2 = instruction(type1, {arg1, arg2});

    REQUIRE(inst2 == inst);
  }

  SECTION("Equality")
  {
    auto const inst = instruction(type1, {arg1, arg2});
    auto const inst2 = instruction(type1, {arg1, arg2});

    REQUIRE(inst == inst2);
  }

  SECTION("Inequality")
  {
    auto const inst = instruction(type1, {arg1, arg2});
    auto const inst2 = instruction(type2, {arg1, arg2});

    REQUIRE(inst != inst2);
  }

  SECTION("Hash")
  {
    auto const inst = instruction(type1, {arg1, arg2});
    auto const inst2 = instruction(type1, {arg1, arg2});

    REQUIRE(std::hash<instruction>{}(inst) == std::hash<instruction>{}(inst2));
  }
}

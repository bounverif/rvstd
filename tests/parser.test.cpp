
#include <boost/url.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("URL")
{
  boost::urls::url u("#/d/e/f");

  REQUIRE(u.encoded_host().empty());
  REQUIRE(u.encoded_path().empty());
  REQUIRE(u.encoded_query().empty());
  REQUIRE(u.encoded_fragment() == "/d/e/f");
  REQUIRE(u.encoded_userinfo().empty());
}

#ifndef RVSTD_PARSER_HPP
#define RVSTD_PARSER_HPP

#include "rvstd/unique_identifier.hpp"

#include <boost/url/parse.hpp>
#include <boost/url/urls.hpp>

namespace rvstd {

auto parse_uri(boost::core::string_view s) -> unique_identifier
{
  boost::system::result<boost::url_view> r = boost::urls::parse_uri(s);

  return {};
}

auto parse_expression(string_view sv) -> unique_identifier;

}  // namespace rvstd

#endif  // RVSTD_PARSER_HPP

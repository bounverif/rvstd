#include "rvstd/envsubst.hpp"

#include <boost/regex.hpp>

#include <sstream>
#include <string>

namespace rvstd {

auto envsubst(const std::string& text) -> std::string
{
  static const boost::regex env_var_pattern{R"--(\$(?:(\w+)|\{([^}]+)\}))--"};
  std::ostringstream result;
  boost::regex_replace(
    std::ostreambuf_iterator<char>(result),
    text.begin(),
    text.end(),
    env_var_pattern,
    [&](const boost::match_results<std::string::const_iterator>& match) {
      std::string var_name_str;
      if(match[1].matched) {
        var_name_str = match[1].str();
      }
      else if(match[2].matched) {
        var_name_str = match[2].str();
      }
      if(const char* ptr = std::getenv(var_name_str.c_str()); ptr != nullptr) {
        return ptr;
      }
      return "";  // Empty string for non-existent variables
    });

  return result.str();  // Return the result stored in the output stream
}

}  // namespace rvstd

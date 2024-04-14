#ifndef RVSTD_ENVSUBST_HPP
#define RVSTD_ENVSUBST_HPP

#include <boost/regex.hpp>

#include <iostream>
#include <regex>
#include <string>

namespace rvstd {

auto envsubst(const std::string& text) -> std::string;

}  // namespace rvstd

#endif  // RYJSOND_ENVSUBST_HPP

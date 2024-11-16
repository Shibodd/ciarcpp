#ifndef CIARCPP_PARSE_HPP
#define CIARCPP_PARSE_HPP

#include <ciarcpp/types.hpp>

namespace ciarcpp {
namespace parse {

Objectives parse_objectives(const std::string& json);

};
};

#endif // !CIARCPP_PARSE_HPP
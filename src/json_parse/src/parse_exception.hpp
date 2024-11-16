#ifndef CIARCPP_PARSE_PARSEEXCEPTION_HPP
#define CIARCPP_PARSE_PARSEEXCEPTION_HPP

#include <stdexcept>

namespace ciarcpp {
namespace parse {

struct JsonParseException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

}; // namespace parse
}; // namespace ciarcpp

#endif // !CIARCPP_PARSE_PARSEEXCEPTION_HPP
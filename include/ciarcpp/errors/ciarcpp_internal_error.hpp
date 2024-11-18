#include <stdexcept>

namespace ciarcpp {

/*
There was a problem with the request or response, which depends on a bug in the ciarcpp library.
E.g.: we're sending a request in the wrong format.
*/
struct CiarcppInternalException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

}; // namespace ciarcpp
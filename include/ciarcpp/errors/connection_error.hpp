#include <stdexcept>

namespace ciarcpp {

/*
There was a problem with the connection itself, before any HTTP data were even transferred.
E.g.: the host is unreachable.
*/
struct ConnectionException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

}; // namespace ciarcpp
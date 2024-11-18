#include <stdexcept>

namespace ciarcpp {

/*
There is a problem that depends on a misuse of the API by the clients of ciarcpp.
E.g.: the satellite is unreachable (you should've booked a slot first!)
*/
struct CiarcLogicException : public std::logic_error {
  using std::logic_error::logic_error;
};

}; // namespace ciarcpp
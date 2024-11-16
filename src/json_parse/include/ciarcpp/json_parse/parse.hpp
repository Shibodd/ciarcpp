#ifndef CIARCPP_PARSE_HPP
#define CIARCPP_PARSE_HPP

#include <ciarcpp/types.hpp>

#define CIARCPP_JSON_MAKE_PARSER(T, name) \
  T parse_##name(const std::string& json)

namespace ciarcpp {
namespace parse {

struct JsonParseException : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

CIARCPP_JSON_MAKE_PARSER(Objectives, objectives);
CIARCPP_JSON_MAKE_PARSER(Observation, observation);
CIARCPP_JSON_MAKE_PARSER(Slots, slots);
CIARCPP_JSON_MAKE_PARSER(Simulation, simulation);
CIARCPP_JSON_MAKE_PARSER(ControlResponse, control_response);

namespace for_testing {
CIARCPP_JSON_MAKE_PARSER(timestamp, timestamp);
CIARCPP_JSON_MAKE_PARSER(std::optional<Zone>, zone);
CIARCPP_JSON_MAKE_PARSER(MelvinState, melvin_state);
}; // namespace for_testing

};
};

#undef CIARCPP_JSON_MAKE_PARSER

#endif // !CIARCPP_PARSE_HPP
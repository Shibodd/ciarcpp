#ifndef CIARCPP_PARSE_HPP
#define CIARCPP_PARSE_HPP

#include <ciarcpp/types.hpp>

#define CIARCPP_JSON_MAKE_PARSER(T, name) \
  T parse_##name(const std::string& json)

namespace ciarcpp {
namespace json_parse {

CIARCPP_JSON_MAKE_PARSER(Objectives, objectives);
CIARCPP_JSON_MAKE_PARSER(ObjectiveAdded, objective_added);
CIARCPP_JSON_MAKE_PARSER(Observation, observation);
CIARCPP_JSON_MAKE_PARSER(Slots, slots);
CIARCPP_JSON_MAKE_PARSER(Slot, slot);
CIARCPP_JSON_MAKE_PARSER(Simulation, simulation);
CIARCPP_JSON_MAKE_PARSER(ControlResponse, control_response);
CIARCPP_JSON_MAKE_PARSER(Achievements, achievements);
CIARCPP_JSON_MAKE_PARSER(BeaconAttemptResponse, beacon_attempt_response);

namespace for_testing {
CIARCPP_JSON_MAKE_PARSER(timestamp, timestamp);
CIARCPP_JSON_MAKE_PARSER(std::optional<Zone>, zone);
CIARCPP_JSON_MAKE_PARSER(MelvinState, melvin_state);
}; // namespace for_testing

}; // namespace json_parse
}; // namespace ciarcpp

#undef CIARCPP_JSON_MAKE_PARSER

#endif // !CIARCPP_PARSE_HPP
#include <ciarcpp/json_parse/parse.hpp>
#include "json_parsers.hpp"
#include "enum_metas.hpp"

#undef CIARCPP_JSON_MAKE_PARSER
#define CIARCPP_JSON_MAKE_PARSER(T, name) \
  T parse_##name(const std::string& json) { return parse_json<T>(json); } struct suca

namespace ciarcpp {
namespace parse {

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

}; // namespace parse
}; // namespace ciarcpp


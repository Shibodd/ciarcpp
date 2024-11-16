#include <ciarcpp/json_parse/parse.hpp>
#include "json_parsers.hpp"

namespace ciarcpp {
namespace parse {

Objectives parse_objectives(const std::string& json) { return parse_json<Objectives>(json); }

}; // namespace parse
}; // namespace ciarcpp


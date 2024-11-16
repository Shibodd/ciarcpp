#include <ciarcpp/api.hpp>
#include <ciarcpp/types.hpp>
#include <ciarcpp/json_parse/parse.hpp>

#include <cpr/cpr.h>
#include <iostream>

namespace ciarcpp {

namespace sync {

Objectives list_objectives(const char* base_url) {
  return parse::parse_objectives("{}");
}

} // namespace sync
} // namespace ciarcpp

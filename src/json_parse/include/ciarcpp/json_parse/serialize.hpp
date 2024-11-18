#ifndef CIARCPP_SERIALIZE_HPP
#define CIARCPP_SERIALIZE_HPP

#include <ciarcpp/types.hpp>

#define CIARCPP_JSON_MAKE_SERIALIZER(T, name) \
  std::string serialize_##name(const T& x)

namespace ciarcpp {
namespace json_parse {

CIARCPP_JSON_MAKE_SERIALIZER(AddObjectives, add_objectives);
CIARCPP_JSON_MAKE_SERIALIZER(Control, control);

}; // namespace json_parse
}; // namespace ciarcpp

#undef CIARCPP_JSON_MAKE_SERIALIZER

#endif // !CIARCPP_SERIALIZE_HPP
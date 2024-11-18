#include "json_serializers.hpp"
#include "enum_metas.hpp"

namespace ciarcpp {
namespace json_parse {

#undef CIARCPP_JSON_MAKE_SERIALIZER
#define CIARCPP_JSON_MAKE_SERIALIZER(T, name) \
  std::string serialize_##name(const T& x) { return serialize_json<T>(x); } struct suca

CIARCPP_JSON_MAKE_SERIALIZER(AddObjectives, add_objectives);
CIARCPP_JSON_MAKE_SERIALIZER(Control, control);

}; // namespace json_parse
}; // namespace ciarcpp
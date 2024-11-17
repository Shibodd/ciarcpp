#ifndef CIARCPP_SERIALIZE_JSONSERIALIZERS_HPP
#define CIARCPP_SERIALIZE_JSONSERIALIZERS_HPP

#include <ciarcpp/json_parse/serialize.hpp>
#include <glaze/glaze.hpp>
#include <date/date.h>

#include "get_type_name.hpp"

namespace ciarcpp {

static std::string format_datetime(const std::chrono::system_clock::time_point& tp) {
  return date::format("%FT%TZ", tp);
}

namespace serialize {

template <typename T>
static inline std::string serialize_json(const T& obj) {
  T cpy = obj; // why does glaze need a non-const reference?? wth
  auto exp = glz::write_json(cpy);
  
  if (bool(exp))
    return exp.value();

  std::ostringstream s;
  s << "While serializing \"" << get_type_name<T>() << "\":\n" << glz::format_error(exp.error());
  throw JsonSerializeException(std::move(s).str());
}

}; // namespace serialize
}; // namespace ciarcpp

namespace glz::detail {

template<>
struct to<JSON, std::chrono::system_clock::time_point> {
  template <auto Opts, is_context Ctx, class... Args>
  static void op(std::chrono::system_clock::time_point& value, Ctx&& ctx, Args&&... args) {
    write<JSON>::op<Opts>(ciarcpp::format_datetime(value), std::forward<Ctx>(ctx), std::forward<Args>(args)...);
  }
};

} // namespace glz::detail


#endif // !CIARCPP_SERIALIZE_JSONSERIALIZERS_HPP
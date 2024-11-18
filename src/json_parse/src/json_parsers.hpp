#ifndef CIARCPP_PARSE_JSONPARSERS_HPP
#define CIARCPP_PARSE_JSONPARSERS_HPP

#include <algorithm>
#include <array>
#include <glaze/glaze.hpp>
#include <date/date.h>

#include <ciarcpp/types.hpp>
#include <ciarcpp/json_parse/parse.hpp>
#include <ciarcpp/errors/ciarcpp_internal_error.hpp>

#include "get_type_name.hpp"

using namespace ciarcpp;

namespace ciarcpp {

static std::optional<std::chrono::system_clock::time_point> parse_datetime(const std::string& s) {
  std::chrono::system_clock::time_point ans;
  std::istringstream ss{s};

  ss >> date::parse("%FT%TZ", ans);
  if (ss.fail())
    return std::nullopt;

  return ans;
}

namespace json_parse {

template <typename T>
static inline T parse_json(const std::string& text) {
  glz::expected exp = glz::read_json<T>(text);
  if (exp)
    return exp.value();
  else {
    std::ostringstream s;
    s << "While parsing JSON for \"" << get_type_name<T>() << "\":\n" << glz::format_error(exp.error(), text);
    throw CiarcppInternalException(std::move(s).str());
  }
}

}; // namespace json_parse
}; // namespace ciarcpp

namespace glz::detail {

template<>
struct from<JSON, std::chrono::system_clock::time_point> {
  template <auto Opts, is_context Ctx, class... Args>
  static void op(std::chrono::system_clock::time_point& value, Ctx&& ctx, Args&&... args) {
    std::string str;
    read<JSON>::op<Opts>(str, std::forward<Ctx>(ctx), std::forward<Args>(args)...);

    if (bool(ctx.error)) [[unlikely]]
      return;

    if (auto val = parse_datetime(str)) {
      value = val.value();
    } else {
      ctx.error = error_code::parse_error;
    }
  }
};

template<>
struct from<JSON, std::optional<Zone>> {
  template <auto Opts, is_context Ctx, class... Args>
  static void op(std::optional<Zone>& value, Ctx&& ctx, Args&&... args) {
    // Try to parse it as a string first
    std::string str;
    read<JSON>::op<Opts>(str, std::forward<Ctx>(ctx), std::forward<Args>(args)...);
    // Was this a string?
    if (not bool(ctx.error)) {
      if (str == "unknown") {
        value = std::nullopt; // Ok, so the zone is just unknown.
        return;
      }

      // We only expect strings with "unknown". Error out.
      ctx.error = error_code::parse_error;
      return;
    }

    // It was not a string - then we expect an integer array representing a rectangle.
    ctx.error = error_code::none; // not being a string is not an error.

    std::array<int, 4> r;
    r.fill(-1); // fill with sentinel
    read<JSON>::op<Opts>(r, std::forward<Ctx>(ctx), std::forward<Args>(args)...);
    if (bool(ctx.error)) {
      return; // not an array
    }

    if (std::ranges::find(r, -1) != r.end()) {
      // Shorter than required
      ctx.error = error_code::parse_error;
      return;
    }
    
    // Rectangle!
    value.emplace(r[0], r[1], r[2], r[3]);
  }
};

}

#endif // !CIARCPP_PARSE_JSONPARSERS_HPP
#include <optional>
#include <date/date.h>

namespace ciarcpp {

static std::optional<std::chrono::system_clock::time_point> parse_datetime(const std::string& s) {
  std::chrono::system_clock::time_point ans;
  std::istringstream ss{s};

  ss >> date::parse("%FT%TZ", ans);
  if (ss.fail())
    return std::nullopt;

  return ans;
}

}
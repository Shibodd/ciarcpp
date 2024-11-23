#include "cpr/api.h"
#include "cpr/buffer.h"
#include <cstring>

#include <ciarcpp/api.hpp>
#include <ciarcpp/types.hpp>
#include <ciarcpp/json_parse/parse.hpp>
#include <ciarcpp/json_parse/serialize.hpp>
#include <ciarcpp/errors/connection_error.hpp>
#include <ciarcpp/errors/ciarc_logic_error.hpp>
#include <ciarcpp/errors/ciarcpp_internal_error.hpp>

#include <cpr/cpr.h>


namespace ciarcpp {

namespace sync {

static inline cpr::Url make_url(const std::string_view& base_url, const std::string_view& resource) {
  std::string url;
  url.reserve(base_url.size() + resource.size() + 1);
  url.append(base_url);
  if (base_url.back() != '/')
    url.push_back('/');
  url.append(resource);
  return url;
}

static inline void success_or_throw(const cpr::Response& response) {
  switch (response.status_code) {
    case 200: // success
      return;

    case 0: { // failure below HTTP
      std::ostringstream ss;
      ss << "Connection error (error code " << (int)response.error.code << "): " << response.error.message << std::endl;
      throw ConnectionException(std::move(ss).str());
    }

    case 422: // Request validation failure
      throw CiarcppInternalException("Request validation failure (status code 422): " + response.text);

    case 400: // CIARC error (e.g. satellite unreachable)
      // TODO: Parse the generic error JSON string. Maybe parse the errors into an enum?
      throw CiarcLogicException(response.text);

    default: {
      std::ostringstream ss;
      ss << "Unknown error (status code " << response.status_code << "): " << response.text << std::endl;
      throw CiarcppInternalException(std::move(ss).str());
    }
  }
}

Slots list_slots(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "slots"));
  success_or_throw(response);
  return json_parse::parse_slots(response.text);
}

Slot book_slot(const char* base_url, int slot_id, bool enabled) {
  auto params = cpr::Parameters({
    { "slot_id", std::to_string(slot_id) },
    { "enabled", enabled? "true" : "false" }
  });
  auto response = cpr::Put(make_url(base_url, "slots"), params);
  success_or_throw(response);
  return json_parse::parse_slot(response.text);
}

void create_backup(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "backup"));
  success_or_throw(response);
  return;
}

void restore_backup(const char* base_url) {
  auto response = cpr::Put(make_url(base_url, "backup"));
  success_or_throw(response);
  return;
}

Objectives list_objectives(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "objective"));
  success_or_throw(response);
  return json_parse::parse_objectives(response.text);
}

ObjectiveAdded add_objective(const char* base_url, AddObjectives objectives) {
  auto header = cpr::Header{ { "Content-Type", "application/json" } };
  auto body = cpr::Body{ json_parse::serialize_add_objectives(objectives) };
  auto response = cpr::Put(make_url(base_url, "objective"), body, header);
  success_or_throw(response);
  return json_parse::parse_objective_added(response.text);
}

void delete_objective(const char* base_url, int id) {
  auto params = cpr::Parameters{
    { "id", std::to_string(id) }
  };
  auto response = cpr::Delete(make_url(base_url, "objective"), params);
  success_or_throw(response);
  return;
}

Simulation configure_simulation(const char* base_url, Simulation sim) {
  auto params = cpr::Parameters {
    { "is_network_simulation", sim.is_network_simulation? "true" : "false" },
    { "user_speed_multiplier", std::to_string(sim.user_speed_multiplier) }
  };
  auto response = cpr::Put(make_url(base_url, "simulation"), params);
  success_or_throw(response);
  return json_parse::parse_simulation(response.text);
}

Achievements list_achievements(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "achievements"));
  success_or_throw(response);
  return json_parse::parse_achievements(response.text);
}

std::string get_image(const char* base_url) {
  auto response = cpr::Get(
    make_url(base_url, "image"),
    cpr::Header{ { "Accept", "image/png" } }
  );
  success_or_throw(response);
  return std::move(response.text);
}

void get_image(const char* base_url, const std::filesystem::path& path) {
  cpr::Response response;

  {
    std::ofstream stream(path);
    response = cpr::Download(stream, make_url(base_url, "image"), cpr::Header{ { "Accept", "image/png" } });
  }

  success_or_throw(response);
}

void upload_objective_image(const char *base_url, int objective_id, const std::filesystem::path &png_path) {
  auto params = cpr::Parameters{ {"objective_id", std::to_string(objective_id)} };
  auto multipart = cpr::Multipart{ { "image", cpr::File{png_path} } };
  auto response = cpr::Post(make_url(base_url, "image"), params, multipart);
  success_or_throw(response);
  return;
}

void upload_daily_map(const char *base_url, const std::filesystem::path &png_path) {
  auto multipart = cpr::Multipart{ { "image", cpr::File{png_path} } };
  auto response = cpr::Post(make_url(base_url, "dailyMap"), multipart);
  success_or_throw(response);
  return;
}

ControlResponse control(const char* base_url, const Control& x) {
  auto body = cpr::Body{ json_parse::serialize_control(x) };
  auto header = cpr::Header{ { "Content-Type", "application/json" } };
  auto response = cpr::Put(make_url(base_url, "control"), body, header);
  success_or_throw(response);
  return json_parse::parse_control_response(response.text);
}

Observation get_observation(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "observation"));
  success_or_throw(response);
  return json_parse::parse_observation(response.text);
}

void reset(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "reset"));
  success_or_throw(response);
  return;
}

BeaconAttemptResponse send_beacon_position(const char* base_url, int beacon_id, int width, int height) {
  auto params = cpr::Parameters {
    { "beacon_id", std::to_string(beacon_id) },
    { "width", std::to_string(width) },
    { "height", std::to_string(height) },
  };
  auto response = cpr::Put(make_url(base_url, "beacon"), params);
  success_or_throw(response);
  return json_parse::parse_beacon_attempt_response(response.text);
}

} // namespace sync
} // namespace ciarcpp

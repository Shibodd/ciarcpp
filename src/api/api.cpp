#include <ciarcpp/api.hpp>
#include <ciarcpp/types.hpp>
#include <ciarcpp/json_parse/parse.hpp>
#include <ciarcpp/json_parse/serialize.hpp>

#include <iostream>

#include <cpr/cpr.h>
#include <cstring>

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

Slots list_slots(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "slots"));
  return parse::parse_slots(response.text);
}

Slot book_slot(const char* base_url, int slot_id, bool enabled) {
  auto params = cpr::Parameters({
    { "slot_id", std::to_string(slot_id) },
    { "enabled", enabled? "true" : "false" }
  });
  auto response = cpr::Put(make_url(base_url, "slots"), params);
  return parse::parse_slot(response.text);
}

void create_backup(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "backup"));
  return;
}

void restore_backup(const char* base_url) {
  auto response = cpr::Put(make_url(base_url, "backup"));
  return;
}

Objectives list_objectives(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "objective"));
  return parse::parse_objectives(response.text);
}

ObjectiveAdded add_objective(const char* base_url, AddObjectives objectives) {
  auto header = cpr::Header{ { "Content-Type", "application/json" } };
  auto body = cpr::Body{ serialize::serialize_add_objectives(objectives) };
  auto response = cpr::Put(make_url(base_url, "objective"), body, header);
  return parse::parse_objective_added(response.text);
}

void delete_objective(const char* base_url, int id) {
  auto params = cpr::Parameters{
    { "id", std::to_string(id) }
  };
  auto response = cpr::Delete(make_url(base_url, "objective"), params);
  return;
}

Simulation configure_simulation(const char* base_url, Simulation sim) {
  auto params = cpr::Parameters {
    { "is_network_simulation", sim.is_network_simulation? "true" : "false" },
    { "user_speed_multiplier", std::to_string(sim.user_speed_multiplier) }
  };
  auto response = cpr::Put(make_url(base_url, "simulation"), params);
  return parse::parse_simulation(response.text);
}

Achievements list_achievements(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "achievements"));
  return parse::parse_achievements(response.text);
}

std::basic_string<char> get_image(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "image"));
  return response.text;
}

void upload_objective_image(const char *base_url, int objective_id, const std::filesystem::path &png_path) {
  auto params = cpr::Parameters{ {"objective_id", std::to_string(objective_id)} };
  auto multipart = cpr::Multipart{ { "image", cpr::File{png_path} } };
  auto response = cpr::Post(make_url(base_url, "image"), params, multipart);
  return;
}

void upload_daily_map(const char *base_url, const std::filesystem::path &png_path) {
  auto multipart = cpr::Multipart{ { "image", cpr::File{png_path} } };
  auto response = cpr::Post(make_url(base_url, "dailyMap"), multipart);
  return;
}

ControlResponse control(const char* base_url, const Control& x) {
  auto body = cpr::Body{ serialize::serialize_control(x) };
  auto header = cpr::Header{ { "Content-Type", "application/json" } };
  auto response = cpr::Put(make_url(base_url, "control"), body, header);
  return parse::parse_control_response(response.text);
}

Observation get_observation(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "observation"));
  return parse::parse_observation(response.text);
}

void reset(const char* base_url) {
  auto response = cpr::Get(make_url(base_url, "reset"));
  return;
}

BeaconAttemptResponse send_beacon_position(const char* base_url, int beacon_id, int width, int height) {
  auto params = cpr::Parameters {
    { "beacon_id", std::to_string(beacon_id) },
    { "width", std::to_string(width) },
    { "height", std::to_string(height) },
  };
  auto response = cpr::Put(make_url(base_url, "beacon"), params);
  return parse::parse_beacon_attempt_response(response.text);
}

} // namespace sync
} // namespace ciarcpp

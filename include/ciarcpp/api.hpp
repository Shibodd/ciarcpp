#ifndef CIARCPP_API_HPP
#define CIARCPP_API_HPP

#include "types.hpp"
#include <filesystem>

namespace ciarcpp {

namespace sync {

Slots list_slots(const char* base_url);
Slot book_slot(const char* base_url, int slot_id, bool enabled);
void create_backup(const char* base_url);
void restore_backup(const char* base_url);
Objectives list_objectives(const char* base_url);
ObjectiveAdded add_objective(const char* base_url, AddObjectives objectives);
void delete_objective(const char* base_url, int id);
Simulation configure_simulation(const char* base_url, Simulation sim);
Achievements list_achievements(const char* base_url);
std::basic_string<char> get_image(const char* base_url);
void upload_objective_image(const char *base_url, int objective_id, const std::filesystem::path &png_path);
void upload_daily_map(const char *base_url, const std::filesystem::path &png_path);
ControlResponse control(const char* base_url, const Control& x);
Observation get_observation(const char* base_url);
void reset(const char* base_url);
BeaconAttemptResponse send_beacon_position(const char* base_url, int beacon_id, int width, int height);

} // namespace sync
} // namespace ciarcpp

#endif // !CIARCPP_API_HPP
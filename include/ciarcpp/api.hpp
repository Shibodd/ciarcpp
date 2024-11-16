#ifndef CIARCPP_API_HPP
#define CIARCPP_API_HPP

#include "types.hpp"
#include <filesystem>

namespace ciarcpp {

namespace sync {
  /* Returns a list of the available slots. */
  Slots list_slots(const char* base_url);
  bool book_slot(const char* base_url, int id, bool enabled);
  void save_backup(const char* base_url);
  void restore_backup(const char* base_url);
  Objectives list_objectives(const char* base_url);

  void upload_objective_image(const char* base_url, int objective_id, const std::filesystem::path& png_path);
  void upload_daily_map(const char* base_url, const std::filesystem::path& png_path);
  Simulation simulation(const char* base_url, const Simulation& sim);
  ControlResponse control(const char* base_url, const Control& ctrl);
  Observation get_observation(const char* base_url);
  
}; // namespace sync
/*
namespace async {
  std::future<void> upload_objective_image(const char* base_url, int objective_id, const std::filesystem::path& png_path);
  std::future<void> upload_daily_map(const char* base_url, const std::filesystem::path& png_path);
  std::future<dto::Simulation> simulation(const char* base_url, const dto::Simulation& sim);
  std::future<dto::ControlResponse> control(const char* base_url, const dto::Control& ctrl);
  std::future<dto::Observation> get_observation(const char* base_url);
  std::future<dto::Slots> list_slots(const char* base_url);
  std::future<bool> book_slot(const char* base_url, int id, bool enabled);
}; // namespace async
*/
}; // namespace ciarcpp

#endif // !CIARCPP_API_HPP

#ifndef CIARCPP_TYPES_HPP
#define CIARCPP_TYPES_HPP

#include <chrono>
#include <vector>
#include <string>
#include <optional>

namespace ciarcpp {

using timestamp = std::chrono::system_clock::time_point;

enum class MelvinState {
  Deployment,
  Safe,
  Communication,
  Charge,
  Acquisition,
  Transition,
  None
};

enum class CameraAngle {
  Narrow,
  Normal,
  Wide
};

struct Observation {
  MelvinState state;
  CameraAngle angle;
  int simulation_speed;
  int width_x;
  int height_y;
  double vx;
  double vy;
  double battery;
  double max_battery;
  double fuel;
  double distance_covered;
  struct {
    double narrow;
    double normal;
    double wide;
  } area_covered;
  struct {
    int data_volume_sent;
    int data_volume_received;
  } data_volume;
  int images_taken;
  int active_time;
  int objectives_done;
  int objectives_points;
  timestamp timestamp;
};

struct Slot {
  int id;
  timestamp start;
  timestamp end;
  bool enabled;
};

struct Slots {
  int communication_slots_used;
  std::vector<Slot> slots;
};

struct Zone {
  int top_left_x;
  int top_left_y;
  int width;
  int height;
  bool operator==(const Zone& other) const = default;
};

struct ZonedObjective {
  int id;
  std::string name;
  timestamp start;
  timestamp end;
  double decrease_rate;
  std::optional<Zone> zone;
  CameraAngle optic_required;
  double coverage_required;
  std::string description;
  std::optional<std::string> sprite;
  bool secret;
};

struct BeaconObjective {
  int id;
  std::string name;
  timestamp start;
  timestamp end;
  double decrease_rate;
  int attempts_made;
  std::string description;
};

struct Objectives {
  std::vector<ZonedObjective> zoned_objectives;
  std::vector<BeaconObjective> beacon_objectives;
};

struct Simulation {
  bool is_network_simulation;
  int user_speed_multiplier;
};

struct Control {
  double vel_x;
  double vel_y;
  CameraAngle camera_angle;
  MelvinState state;
};

struct ControlResponse {
  double vel_x;
  double vel_y;
  CameraAngle camera_angle;
  MelvinState state;
  std::string status;
};

struct GenericError {
  std::string detail;
};



}; // namespace ciarcpp

#endif // !CIARCPP_TYPES_HPP
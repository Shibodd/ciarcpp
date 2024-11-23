#ifndef CIARCPP_TYPES_HPP
#define CIARCPP_TYPES_HPP

#include <chrono>
#include <vector>
#include <string>
#include <optional>
#include <variant>

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
  double active_time;
  int objectives_done;
  int objectives_points;
  timestamp timestamp;

  operator struct Control();
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

struct AddBeaconObjective {
  int id;
  std::string name;
  timestamp start;
  timestamp end;
  double decrease_rate;
  std::string description;
  int beacon_height;
  int beacon_width;
  int attempts_made;
};

struct AddObjectives {
  std::vector<ZonedObjective> zoned_objectives;
  std::vector<AddBeaconObjective> beacon_objectives;
};

struct ObjectiveAdded {
  std::vector<int> added;
  std::vector<int> modified;
};

struct Simulation {
  bool is_network_simulation;
  int user_speed_multiplier;
  bool operator==(const Simulation& other) const = default;
};

struct Control {
  double vel_x;
  double vel_y;
  CameraAngle camera_angle;
  MelvinState state;
  bool operator==(const Control& other) const = default;
};

inline Observation::operator Control() {
  return Control {
    .vel_x = vx,
    .vel_y = vy,
    .camera_angle = angle,
    .state = state
  };
}

struct ControlResponse {
  double vel_x;
  double vel_y;
  CameraAngle camera_angle;
  MelvinState state;
  std::string status;

  operator Control() {
    return Control {
      .vel_x = vel_x,
      .vel_y = vel_y,
      .camera_angle = camera_angle,
      .state = state
    };
  }
};

struct Achievement {
  std::string name;
  bool done;
  int points;
  std::string description;
  std::variant<bool, double, std::string> goal_parameter_threshold;
  std::variant<bool, double, std::string> goal_parameter;
};

struct BeaconAttemptResponse {
  std::string status;
  int attempts_made;
};

struct Achievements {
  std::vector<Achievement> achievements;
};

struct GenericError {
  std::string detail;
};



}; // namespace ciarcpp

#endif // !CIARCPP_TYPES_HPP
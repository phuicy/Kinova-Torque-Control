#include "KinovaRobot.h"

#include "rclcpp/rclcpp.hpp"
#include <BaseCyclicClientRpc.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <math.h>
#include <numeric>
#include <time.h>

KinovaRobot::KinovaRobot(std::string name_, std::string address,
                         std::string username, std::string password)
    : name(name_) {
  setState("Unintialised");
  ;
  last_time = std::chrono::high_resolution_clock::now();
  times.reserve(averaging_window);

  position_last = Eigen7f::Zero();
  velocity_last = Eigen7f::Zero();

  base_command = new BaseCyclic::Command();
}

KinovaRobot::~KinovaRobot() { std::cout << "Deleting kinova" << std::endl; }

bool KinovaRobot::home() {
  RCLCPP_INFO_STREAM(rclcpp::get_logger("Kinova"), name << " homed");
  Eigen7f actual, velocity, torque;
  actual = Eigen7f::Random();
  velocity = Eigen7f::Random();
  torque = Eigen7f::Random();
  set_pose(actual);
  set_velocity(velocity);
  set_torque(torque);
  setState("Homed");
  return true;
}

void KinovaRobot::get(const Kinova::Api::BaseCyclic::Feedback* base_feedback) {
  Eigen7f actual, velocity, torque;
  if (first) {
    first = false;

    actual = Eigen7f::Random();
    velocity = Eigen7f::Random();
    torque = Eigen7f::Random();
    torque_last = torque;
  } else {
    actual = position_last;
    velocity = velocity_last;
    torque = torque_last;
  }

  set_pose(actual);
  set_velocity(velocity);
  set_torque(torque);
}

void KinovaRobot::set(Eigen7f command) {
  auto time = std::chrono::high_resolution_clock::now();
  torque_last = command;
  velocity_last += command / 1000.0;
  position_last += velocity_last / 1000.0;

  auto frame_id = base_command->frame_id() + 1;
  base_command->set_frame_id(frame_id);
  if (frame_id > 65535)
    base_command->set_frame_id(0);
  for (unsigned int i = 0; i < KinovaRobot::actuator_count; i++) {
    // Save the current actuator position, to avoid a following error
    base_command->mutable_actuators(i)->set_command_id(frame_id);
    base_command->mutable_actuators(i)->set_position(0);
    base_command->mutable_actuators(i)->set_torque_joint(command[i]);

    get(nullptr);
  }

  using namespace std::chrono;
  duration<double, std::milli> ms_double = time - last_time;
  last_time = time;

  times.push_back(ms_double.count());

  if (step > averaging_window - 1) {
    step = 0;
    double aw = averaging_window;
    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double mean = sum / aw;

    double sq_sum =
        std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / times.size() - mean * mean);
    auto max = std::max_element(times.begin(), times.end());
    auto min = std::min_element(times.begin(), times.end());
    std::cout << "robot:" << name << std::endl;
    std::cout << "mean: " << mean << "ms -- std: " << stdev
              << "ms -- max: " << *max << "ms -- min: " << *min << "ms "
              << std::endl;
    times.clear();
    std::cout << "command:" << command << std::endl;

    last_time = std::chrono::high_resolution_clock::now();
  }
  step++;
}

void KinovaRobot::torqueMode() {
  RCLCPP_INFO_STREAM(rclcpp::get_logger("Kinova"),
                     name << " Low Leveling Processing mode");
  // Initialize each actuator to their current position
  unsigned int actuator_count = 7;
  for (unsigned int i = 0; i < actuator_count; i++) {
    // Save the current actuator position, to avoid a following error
    base_command->add_actuators()->set_position(0);
  }
  setState("Torque mode");
}

void KinovaRobot::positionMode() {
  RCLCPP_INFO_STREAM(rclcpp::get_logger("Kinova"),
                     name << " High Leveling Processing mode");
  setState("Position Mode");
}

bool KinovaRobot::clearFault() {
  RCLCPP_INFO_STREAM(rclcpp::get_logger("Kinova"), name << " Clear Fault");

  return true;
}

void KinovaRobot::getAllDevices() {}
/**
 * @file KinovaRobot.h
 * @author Guy Burroughes
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
/// \cond 
#include <array>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>
/// \endcond 

#include "Utils.h"


namespace Kinova {
namespace Api {
class TransportClientTcp;
class TransportClientUdp;
class RouterClient;
namespace Session {
class CreateSessionInfo;
}
class SessionManager;
namespace Base {
class BaseClient;
}
namespace BaseCyclic {
class BaseCyclicClient;
class Feedback;
class Command;
} // namespace BaseCyclic
namespace ActuatorConfig {
class ActuatorConfigClient;
}
} // namespace Api
} // namespace Kinova

using namespace Kinova::Api;
/**
 * @brief Kinova robot hardware interface
 *
 */
class KinovaRobot {
public:
  /**
   * @brief Construct a new Kinova Robot object
   *
   * @param name Name of the robot
   * @param address Ip address of the robot
   * @param username username of the robot
   * @param password password of the robot
   */
  KinovaRobot(std::string name, std::string address,
              std::string username = "admin", std::string password = "admin");
  /**
   * @brief Destroy the Kinova Robot object
   *
   */
  ~KinovaRobot();
  /**
   * @brief Will attempt to move the kinova to CMS_HOME
   *
   * @return true Robot homed successfully
   * @return false robot failed to home
   */
  bool home();
  /**
   * @brief set local cache of current robot location. Requires feedback input
   *
   * @param base_feedback feeback input from robot
   */
  void get(const Kinova::Api::BaseCyclic::Feedback *base_feedback);
  /**
   * @brief Set position of the robot (and times loop)
   *
   * @param command control input (torque in Nm)
   */
  void set(Eigen7f command);
  /**
   * @brief Get the current pose  (thread safe)
   *
   * @return Eigen7f current pose (degrees)
   */
  Eigen7f get_pose() {
    std::lock_guard<std::mutex> lk(mtx_pose);
    return cached_pose;
  };
  /**
   * @brief Get the current velocity (thread safe)
   *
   * @return Eigen7f current velocity (degrees/s)
   */
  Eigen7f get_velocity() {
    std::lock_guard<std::mutex> lk(mtx_velocity);
    return cached_velocity;
  };
  /**
   * @brief Get the current torque (thread safe)
   *
   * @return Eigen7f current torque (Nm)
   */
  Eigen7f get_torque() {
    std::lock_guard<std::mutex> lk(mtx_torque);
    return cached_torque;
  };
  /**
   * @brief Get the command
   *
   * @return Eigen7f current command (Nm)
   */
  Eigen7f get_command() {
    std::lock_guard<std::mutex> lk(mtx_command);
    return cached_command;
  };
  /**
   * @brief Set the command
   *
   * @param actual actual command (torque)
   */
  void set_command(Eigen7f actual) {
    std::lock_guard<std::mutex> lk(mtx_command);
    cached_command = actual;
  }
  /**
   * @brief Set robot in to torque mode.
   * Require 1khz control set()
   */
  void torqueMode();
  /**
   * @brief Set robot into position high level control mode
   *
   */
  void positionMode();
  /**
   * @brief Attempt to clear any faults of the robot
   *
   * @return true Succesfully cleared faults if there were any
   * @return false Didnt clear faults, robot won't continue
   */
  bool clearFault();
  /**
   * @brief Get the All connected Devices
   *
   */
  void getAllDevices();

  void setState(std::string state_){
    std::lock_guard<std::mutex> lk(mtx_state);
    state = state_;
  }

  std::string getState(){
    std::lock_guard<std::mutex> lk(mtx_state);
    return state;
  }

private:
  void set_pose(Eigen7f actual) {
    std::lock_guard<std::mutex> lk(mtx_pose);
    cached_pose = actual;
  }
  void set_velocity(Eigen7f actual) {
    std::lock_guard<std::mutex> lk(mtx_velocity);
    cached_velocity = actual;
  }
  void set_torque(Eigen7f actual) {
    std::lock_guard<std::mutex> lk(mtx_torque);
    cached_torque = actual;
  }

public:
  /**
   * @brief Name of the robot.
   *
   */
  const std::string name;
  /**
   * @brief Number of joints in the robot.
   * 
   */
  static constexpr unsigned int actuator_count = 7;

private:
  // API objects
  TransportClientTcp *transport;
  RouterClient *router;

  TransportClientUdp *transport_real_time;
  RouterClient *router_real_time;

  // session data connection information
  Session::CreateSessionInfo *create_session_info;

  // Session manager service wrapper
  SessionManager *session_manager;
  SessionManager *session_manager_real_time;

  // services
  Base::BaseClient *base;
  BaseCyclic::BaseCyclicClient *base_cyclic;
  // BaseCyclic::Feedback *base_feedback;
  ActuatorConfig::ActuatorConfigClient *actuator_config;

  BaseCyclic::Command *base_command;

  // Cached
  std::mutex mtx_pose, mtx_velocity, mtx_torque, mtx_command, mtx_state;
  Eigen7f cached_pose, cached_velocity, cached_torque, cached_command;

  // Timing variables
  std::chrono::high_resolution_clock::time_point last_time;
  std::vector<double> times;
  unsigned int step;
  const static unsigned int averaging_window = 500;

  // Mocking variables
  bool first = true;
  Eigen7f torque_last, velocity_last, position_last;

  // State
  std::string state;
};

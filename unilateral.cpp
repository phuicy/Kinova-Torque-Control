/**
 * @file unilateral.cpp
 * @author Guy Burroughes
 * @brief The main file for the unilateral executable
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/// \cond
#include <chrono>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <stdlib.h>
#include <string>
#include <thread>
#include <std_srvs/srv/trigger.hpp>
/// \endcond 

#include "DemandSubscriber.h"
#include "Input.h"
#include "JointStatePublisher.h"
#include "KinovaControl.h"
#include "KinovaRobot.h"
#include "LoopCycle.h"

using namespace std;

/**
 * @brief desired Position and Velocity for PD controller.
 *
 */
Eigen7f firstPosition, firstVelocity;

auto home_local = std::make_shared< std::atomic<bool> >();
auto robot_start = std::make_shared< std::atomic<bool> >();
auto robot_stop = std::make_shared< std::atomic<bool> >();

void home_trigger(const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
          std::shared_ptr<std_srvs::srv::Trigger::Response>      response)
{
  *home_local = true;
  response->success = true;
}
void robot_start_trigger(const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
          std::shared_ptr<std_srvs::srv::Trigger::Response>      response)
{
  *robot_start = true;
  response->success = true;
}
void robot_stop_trigger(const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
          std::shared_ptr<std_srvs::srv::Trigger::Response>      response)
{
  *robot_stop = true;
  response->success = true;

}

/*! \file */
/**
 * @brief Main entry point of programm
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
  // Set Environment variables
  set_env_var();

  // Initialise ROS2
  rclcpp::init(argc, argv);

  // Initialise variable
  rclcpp::Node::SharedPtr node = 
      std::make_shared<rclcpp::Node>("kinova_unilateral");
  RCLCPP_INFO(rclcpp::get_logger("Main"), "Connecting to robots.");
  auto robot = std::make_shared<KinovaRobot>("robot", "192.168.1.16");
  auto robotControl = std::make_shared<KinovaControl>("robot", robot, node);

  rclcpp::executors::MultiThreadedExecutor executor;
  auto robotPublisher = std::make_shared<JointStatePublisher>(robot);

  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_home =
    node->create_service<std_srvs::srv::Trigger>("home_robot", &home_trigger);
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_start =
    node->create_service<std_srvs::srv::Trigger>("robot_start", &robot_start_trigger);
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_stop  =
    node->create_service<std_srvs::srv::Trigger>("robot_stop", &robot_stop_trigger);

  executor.add_node(robotPublisher);
  executor.add_node(node);
  executor.add_node(robotControl->getPdController());

  // Set up Loop cycle
  std::shared_ptr<LoopCycle> loopCycle =
      std::make_shared<LoopCycle>(node, robot, robotControl);
  // Set Initial Demand
  Eigen7f home = Eigen7f::Zero();
  home[1] = 270;
  home[3] = 90;
  home[5] = 90;

  firstPosition = home;
  firstVelocity = Eigen7f::Zero();
  loopCycle->setDemand(firstPosition, firstVelocity);

  // Set up demand subscriber
  auto demandSubscriber = std::make_shared<DemandSubscriber>(
      "demandSubscriber", "demand", loopCycle);
  executor.add_node(demandSubscriber);

  // Declare ROS2 parameters
  node->declare_parameter<bool>("lateral_run", false);
  rclcpp::Parameter action_param("lateral_run", false);

  while (rclcpp::ok()) {

    // set stop parameter
    action_param = rclcpp::Parameter("lateral_run", false);
    node->set_parameter(action_param);

    // Clear Faults
    robot->clearFault();

    // Home the robot
    RCLCPP_INFO(rclcpp::get_logger("Main"), "Ready to home robot.");
    RCLCPP_INFO(rclcpp::get_logger("Main"), "Home the robot? [Y/n]");
    auto cont = spin_till_input(&executor, home_local);
    if (!cont)
      return 0;
    RCLCPP_INFO(rclcpp::get_logger("Main"), "Homing robot.");
    // Clear Faults
    robot->clearFault();
    robot->home();

    // Clear Faults
    robot->clearFault();

    // Start Control
    RCLCPP_INFO(rclcpp::get_logger("Main"), "Start control? [Y/n]");
    cont = spin_till_input(&executor, robot_start);
    if (!cont)
      return 0;
    RCLCPP_INFO(rclcpp::get_logger("Main"),
                "Starting control unilateral robot.");

    // Start loop thread
    std::thread runner(&LoopCycle::loop, loopCycle);

    // Spin ROS2 services
    // executor.spin();
    RCLCPP_INFO(rclcpp::get_logger("Main"), "Press enter to stop!");
    //execute_till_keypress(&executor);
    cont = spin_till_input(&executor, robot_stop);
    RCLCPP_INFO(rclcpp::get_logger("Main"), "Pausing");

    // set stop parameter
    action_param = rclcpp::Parameter("lateral_run", true);
    node->set_parameter(action_param);

    // Stop threads and exit
    runner.join();
  }
  rclcpp::shutdown();
  return 0;
}

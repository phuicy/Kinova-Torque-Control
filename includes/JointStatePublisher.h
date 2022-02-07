/**
 * @file JointStatePublisher.h
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
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/string.hpp"
/// \endcond


#include "KinovaRobot.h"


using namespace std::chrono_literals;

/**
 * @brief A ROS2 node that runs in a executor thread to allow ros logging
 * without limiting 1k loop.
 *
 */
class JointStatePublisher : public rclcpp::Node {
public:
  /**
   * @brief Construct a new Joint State Publisher object
   *
   * @param k_ Robot hardware interface
   */
  explicit JointStatePublisher(std::shared_ptr<KinovaRobot> k_);

private:
  /**
   * @brief The timed callback which publishes the robot state.
   *
   */
  void timer_callback();

private:
  /**
   * @brief Timer for ROS publisher
   *
   */
  rclcpp::TimerBase::SharedPtr timer_;
  /**
   * @brief Robot joint state message to send
   *
   */
  sensor_msgs::msg::JointState robot_message;
  /**
   * @brief Robot command message to send
   * 
   */
  sensor_msgs::msg::JointState command_message;

  std_msgs::msg::String state_message;
  /**
   * @brief Robot joint state message publisher
   * 
   */
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr robot_publisher_;
  /**
   * @brief Command message publisher
   * 
   */
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr command_publisher_;

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_publisher_;

  /**
   * @brief Shared pointer to robot hardware interface to get cached pose, velocity and torque.
   * 
   */
  std::shared_ptr<KinovaRobot> k;
};
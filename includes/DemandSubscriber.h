/**
 * @file DemandSubscriber.h
 * @author Guy Burroughes
 * @brief 
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

/// \cond 
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
/// \endcond 

#include "LoopCycle.h"

using std::placeholders::_1;

/**
 * @brief A subscriber that reads a joint state message and sets the demand pose
 * and velocity for unilateral.
 *
 */
class DemandSubscriber : public rclcpp::Node {
public:
  /**
   * @brief Construct a new Demand Subscriber object
   *
   * @param name Node name
   * @param topic topic name
   * @param loopCycle the loop cycle object to set demand to
   */
  DemandSubscriber(std::string name, std::string topic,
                   std::shared_ptr<LoopCycle> loopCycle);

private:
  void topic_callback(const sensor_msgs::msg::JointState::SharedPtr msg) const;

  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
  std::shared_ptr<LoopCycle> loopCycle;
  static constexpr unsigned int actuator_count = 7;
};
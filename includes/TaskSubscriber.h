/**
 * @file TaskSubscriber.h
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
#include "geometry_msgs/msg/twist.hpp"
/// \endcond 

#include "LoopCycle.h"

using std::placeholders::_1;

/**
 * @brief A subscriber that reads a twist message and sets the demand twist for unilateral.
 *
 */
class TaskSubscriber : public rclcpp::Node {
public:
  /**k
   * @brief Construct a new Task Subscriber object
   *
   * @param name Node name
   * @param topic topic name
   * @param loopCycle the loop cycle object to set demand to
   */
  TaskSubscriber(std::string name, std::string topic,
                   std::shared_ptr<LoopCycle> loopCycle);

private:
  void topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const;

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
  std::shared_ptr<LoopCycle> loopCycle;
  static constexpr unsigned int actuator_count = 7;
};
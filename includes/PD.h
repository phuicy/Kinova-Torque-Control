/**
 * @file PD.h
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
#include <atomic>
#include <rclcpp/rclcpp.hpp>
#include <string>
/// \endcond 

#include "Utils.h"

/**
 * @brief A PD controller that work in degrees [0,360]
 * Loops around 360 inflection point.
 * Kp and Kd are ROS params that update every 500ms.
 */
class PDController : public rclcpp::Node {
public:
  /**
   * @brief Construct a new PDController object
   *
   * @param name Name of robot under control.
   */
  explicit PDController(std::string name);

  /**
   * @brief updates Kp and Kd from ROS params, is running in a thread
   *
   */
  void respond();
  /**
   * @brief Calculate control response for PD kp(pB-pA) + Kd(qB-qA)
   *
   * @param pActual actual position
   * @param pDemand request position
   * @param qActual actual velocity
   * @param qDemand request velocity
   * @return Eigen7f control u
   */
  Eigen7f calculate(Eigen7f pActual, Eigen7f pDemand, Eigen7f qActual, Eigen7f qDemand);

  /**
   * @brief Get the Kp object (thread safe)
   *
   * @return Eigen7f Kp
   */
  Eigen7f getKp();
  /**
   * @brief Get the Kd object (thread safe)
   *
   * @return Eigen7f Kd
   */
  Eigen7f getKd();

private:
  /**
   * @brief Set the Kp object (thread safe)
   *
   * @param Kp_
   */
  void setKp(Eigen7f Kp_);
  /**
   * @brief Set the Kd object (thread safe)
   *
   * @param Kd_
   */
  void setKd(Eigen7f Kd_);

private:
  /**
   * @brief Control multipliers
   *
   */
  Eigen7f Kp, Kd;
  /**
   * @brief Locks for thread safe setters an getters of Kp and Kd
   *
   */
  std::mutex lock_kp, lock_kd;
  /**
   * @brief Timer for thread ros parameter updater
   * 
   */
  rclcpp::TimerBase::SharedPtr timer_;
  /**
   * @brief Robot name
   * 
   */
  std::string name;
};

/**
 * @file Gravity.h
 * @author Guy Burroughes
 * @brief 
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "Utils.h"

/**
 * @brief Auto-generated function which calculates gravity vector torque per joint.
 * 
 * @param q joint angles in degrees
 * @param G Torque to balance gravity at each joint (Nm)
 */
void gravity(const Eigen::Matrix<float, 7, 1> q, Eigen::Matrix<float, 7, 1> &G);
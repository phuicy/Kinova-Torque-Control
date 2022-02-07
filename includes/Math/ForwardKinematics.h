/**
 * @file ForwardKinematics.h
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
 * @brief Auto generated forward kinematics, calculate end-effector position
 * from joint angles
 *
 * @param q joint angles in degrees
 * @param x solved position of end effector in meters.
 * @param R Rotation in matrix form
 */
void forward_kinematics(const Eigen::Matrix<float, 7, 1> q,
                        Eigen::Matrix<float, 3, 1> &x,
                        Eigen::Matrix<float, 3, 3> &R);

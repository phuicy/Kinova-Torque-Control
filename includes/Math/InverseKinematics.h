/**
 * @file InverseKinematics.h
 * @author Ozan Tokatli
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
 * @brief Calculate the inverse kinematics
 * 
 * @param q Current pose (Degrees)
 * @param xp Twist demand (x, y, z, r, p, yaw)
 * @param qp Joint velocuty command (Degrees/s)
 */
void inverse_kinematics(const Eigen::Matrix<float, 7, 1> q,
                        const Eigen::Matrix<float, 6, 1> xp,
                        Eigen::Matrix<float, 7, 1> &qp);

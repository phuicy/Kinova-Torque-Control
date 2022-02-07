/**
 * @file Utils.h
 * @author Guy Burroughes
 * @brief Shared defines
 * @version 0.1
 * @date 2021-12-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <Eigen/Dense>

#define DEG2RAD * M_PI/180.0f 
#define RAD2DEG * 180.0f/M_PI 

/**
 * @brief Float eigen array with 7 elements.
 * 
 */
typedef Eigen::Matrix<float, 7, 1> Eigen7f;
typedef Eigen::Matrix<float, 6, 1> Eigen6f;

/**
 * @brief Float Eigen Matrix with 7x7 elements.
 * 
 */
typedef Eigen::Matrix<float, 7, 7> Eigen7x7f;


typedef Eigen::Matrix<float, 6, 6> Eigen6x6f;
typedef Eigen::Matrix<float, 7, 6> Eigen7x6f;
typedef Eigen::Matrix<float, 6, 7> Eigen6x7f;


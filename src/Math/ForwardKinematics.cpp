#include "Math/ForwardKinematics.h"

void forward_kinematics(const Eigen::Matrix<float, 7, 1> q,
                        Eigen::Matrix<float, 3, 1> &x,
                        Eigen::Matrix<float, 3, 3> &R) {
  const float q1 = q(0);
  const float q2 = q(1);
  const float q3 = q(2);
  const float q4 = q(3);
  const float q5 = q(4);
  const float q6 = q(5);
  const float q7 = q(6);

  const float x0 = sin(q1);
  const float x1 = cos(q3);
  const float x2 = x0 * x1;
  const float x3 = cos(q1);
  const float x4 = sin(q2);
  const float x5 = x3 * x4;
  const float x6 = cos(q4);
  const float x7 = x5 * x6;
  const float x8 = cos(q2);
  const float x9 = sin(q3);
  const float x10 = x3 * x9;
  const float x11 = x10 * x8;
  const float x12 = sin(q4);
  const float x13 = x0 * x9;
  const float x14 = x1 * x3;
  const float x15 = -x13 + x14 * x8;
  const float x16 = x12 * x15;
  const float x17 = cos(q6);
  const float x18 = -x16 - x7;
  const float x19 = x17 * x18;
  const float x20 = sin(q6);
  const float x21 = sin(q5);
  const float x22 = x11 + x2;
  const float x23 = cos(q5);
  const float x24 = -x12 * x5 + x15 * x6;
  const float x25 = -x21 * x22 + x23 * x24;
  const float x26 = x20 * x25;
  const float x27 = x0 * x4;
  const float x28 = x27 * x6;
  const float x29 = x13 * x8;
  const float x30 = -x10 - x2 * x8;
  const float x31 = x12 * x30;
  const float x32 = x28 - x31;
  const float x33 = x17 * x32;
  const float x34 = x14 - x29;
  const float x35 = x12 * x27 + x30 * x6;
  const float x36 = -x21 * x34 + x23 * x35;
  const float x37 = x20 * x36;
  const float x38 = x4 * x9;
  const float x39 = x6 * x8;
  const float x40 = x1 * x4;
  const float x41 = x12 * x40;
  const float x42 = -x39 + x41;
  const float x43 = x17 * x42;
  const float x44 = -x12 * x8 - x40 * x6;
  const float x45 = x21 * x38 + x23 * x44;
  const float x46 = x20 * x45;
  const float x47 = sin(q7);
  const float x48 = x21 * x24 + x22 * x23;
  const float x49 = cos(q7);
  const float x50 = x17 * x25 + x18 * x20;
  const float x51 = x21 * x35 + x23 * x34;
  const float x52 = x17 * x36 + x20 * x32;
  const float x53 = x21 * x44 - x23 * x38;
  const float x54 = x17 * x45 + x20 * x42;

  x << -0.0118 * x0 - 0.0128 * x11 + 0.3143 * x16 - 0.1674 * x19 - 0.0128 * x2 +
           0.1674 * x26 + 0.4208 * x5 + 0.3143 * x7,
      -0.0128 * x14 - 0.4208 * x27 - 0.3143 * x28 + 0.0128 * x29 - 0.0118 * x3 +
          0.3143 * x31 - 0.1674 * x33 + 0.1674 * x37,
      0.0128 * x38 + 0.3143 * x39 - 0.3143 * x41 - 0.1674 * x43 + 0.1674 * x46 +
          0.4208 * x8 + 0.2848;

  R << -x47 * x48 + x49 * x50, x47 * x50 + x48 * x49, -x19 + x26,
      -x47 * x51 + x49 * x52, x47 * x52 + x49 * x51, -x33 + x37,
      -x47 * x53 + x49 * x54, x47 * x54 + x49 * x53, -x43 + x46;
}

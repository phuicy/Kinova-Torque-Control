#include "KinovaControl.h"
#include "KinovaRobot.h"
#include "RobotMath.h"
#include <gtest/gtest.h>

// The fixture for testing class Foo.
class KinovaRobotTest : public ::testing::Test {
protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  KinovaRobotTest() {
    // You can do set-up work for each test here.
  }

  ~KinovaRobotTest() override {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  void TearDown() override {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

// Demonstrate some basic assertions.
TEST(RobotMathTest, MassMatrix) {
  Eigen7f z = Eigen7f::Zero();

  Eigen::Matrix<float, 7, 7> M;
  clock_t t = clock();
  mass_matrix(z, M);
  const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
  ASSERT_TRUE(work_time <= 0.003);

  std::cout << "Time to calculate: " << work_time << std::endl;

  std::cout << "Mass Matrix at home:" << std::endl << M << std::endl;
  std::cout << "Inverse Mass Matrix at home:" << std::endl << M.inverse() << std::endl;

}

// Demonstrate some basic assertions.
TEST(RobotMathTest, GravityVectorTime) {
  Eigen7f z = Eigen7f::Zero();

  Eigen::Matrix<float, 7, 1> g;
  clock_t t = clock();
  gravity(z, g);
  const double work_time = (clock() - t) / double(CLOCKS_PER_SEC);
  ASSERT_TRUE(work_time <= 0.0003);

  std::cout << "Time to calculate: " << work_time << std::endl;
}

/**
 * @brief Gravity in home position test.
 * 
 */
TEST(RobotMathTest, GravityVector) {
  Eigen7f z = Eigen7f::Zero();

  z[1] = 270;
  z[3] = 90;
  z[5] = 90;

  Eigen::Matrix<float, 7, 1> g;
  gravity(z, g);

  Eigen7f gExpect = Eigen7f::Zero();
  gExpect[0] =   1.0;
  gExpect[1] = - 9.0;
  gExpect[2] =   0.0;
  gExpect[3] = - 9.0;
  gExpect[4] = 0.0;
  gExpect[5] = 0.0;
  gExpect[6] = 0.0;


  ASSERT_TRUE(g.isApprox(gExpect, 0.5)) << g;
}

/**
 * @brief Gravity in home position rotated by 90 degrees test.
 * 
 */
TEST(RobotMathTest, RotatedGravityVector) {
  Eigen7f z = Eigen7f::Zero();

  z[0] = 90;
  z[1] = 270;
  z[3] = 90;
  z[5] = 90;

  Eigen::Matrix<float, 7, 1> g;
  gravity(z, g);

  Eigen7f gExpect = Eigen7f::Zero();
  gExpect[0] = -17.0;
  gExpect[1] =   0.0;
  gExpect[2] =   9.0;
  gExpect[3] =   0.0;
  gExpect[4] =   3.0;
  gExpect[5] =   0.0;
  gExpect[6] =   0.0;


  ASSERT_TRUE(g.isApprox(gExpect, 0.5)) << g;
}


/**
 * @brief Corioilis in static home position test.
 * 
 */
TEST(RobotMathTest, CoriolisVectorStatic) {
  Eigen7f z = Eigen7f::Zero();
  Eigen7f v = Eigen7f::Zero();

  z[1] = 270;
  z[3] = 90;
  z[5] = 90;

  Eigen::Matrix<float, 7, 1> c;
  coriolis(z, v, c);

  Eigen7f cExpect = Eigen7f::Zero();


  ASSERT_TRUE(c.isApprox(cExpect, 0.01)) << c;
}


/**
 * @brief Corioilis in moving home position test.
 * 
 */
TEST(RobotMathTest, CoriolisVectorMoving) {
  Eigen7f z = Eigen7f::Zero();
  Eigen7f v = Eigen7f::Zero();

  z[1] = 270;
  z[3] = 90;
  z[5] = 90;

  v[1] = 1;

  Eigen::Matrix<float, 7, 1> c;
  coriolis(z, v, c);

  Eigen7f cExpect = Eigen7f::Zero();
  cExpect[0] = -0.0;
  cExpect[3] =  0.0;
  cExpect[5] =  0.0;


  ASSERT_TRUE(cExpect.isApprox(c, 0.2)) << c  << std::endl  << "cExpect:"<< std::endl  << cExpect;
}


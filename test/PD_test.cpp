#include "PD.h"
#include "rclcpp/rclcpp.hpp"
#include <gtest/gtest.h>

class PDTestFixture : public ::testing::Test {
protected:
  std::shared_ptr<PDController> pdController;

  void SetUp() override {
    // initialize ROS
    rclcpp::init(0, nullptr);

    pdController = std::make_shared<PDController>("test");
  }

  void TearDown() override {
    // shutdown ROS
    rclcpp::shutdown();
  }
};

// Demonstrate some basic assertions.
TEST_F(PDTestFixture, PDCreate) {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
}

TEST_F(PDTestFixture, PDCalculateP) {
  Eigen7f v = Eigen7f::Zero();
  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = -0.1;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateD) {
  Eigen7f v = Eigen7f::Zero();
  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1;

  auto u = this->pdController->calculate(v, v, pA, pB);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = -0.05;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculatePD) {
  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1;

  auto u = this->pdController->calculate(pA, pB, pA, pB);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = -0.15;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

#include <string_view>

void print_map(std::string_view comment,
               const std::map<std::string, float> &m) {
  std::cout << comment;
  for (const auto &[key, value] : m) {
    std::cout << key << " = " << value << "; ";
  }
  std::cout << "\n";
}

TEST_F(PDTestFixture, PDsetKp) {
  Eigen7f v = Eigen7f::Zero();
  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1;

  std::vector<std::string> s{};

  rclcpp::Parameter p("test./joint_1/Kp", 1.0f);

  using namespace std::chrono_literals;

  auto parameters_client =
      std::make_shared<rclcpp::SyncParametersClient>(this->pdController);
  while (!parameters_client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      // RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the
      // service. Exiting.");
      rclcpp::shutdown();
    }
    // RCLCPP_INFO(this->get_logger(), "service not available, waiting
    // again...");
  }

  // Set several different types of parameters.

  auto set_parameters_results = parameters_client->set_parameters({p});

  this->pdController->respond();

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = -1.0;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopA) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 359.0; 
  pB[0] = 1.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = 0.2;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopB) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1.0;
  pB[0] = 359.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = -0.2;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopC) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1.0;
  pB[0] = 171.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = 17.0f;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopD) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1.0;
  pB[0] = 171.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = 17.0f;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopE) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 1.0;
  pB[0] = 191.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = -17.0f;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopF) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 340.0;
  pB[0] = 150.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = 17.0f;

  EXPECT_TRUE(u.isApprox(uA)) << u << std::endl << uA;
}

TEST_F(PDTestFixture, PDCalculateLoopG) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 190.0;
  pB[0] = 340.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = 15.0f;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}

TEST_F(PDTestFixture, PDCalculateLoopH) {
  Eigen7f v = Eigen7f::Zero();

  Eigen7f pA = Eigen7f::Zero();
  Eigen7f pB = Eigen7f::Zero();

  pA[0] = 83.0;
  pB[0] = 90.0;

  auto u = this->pdController->calculate(pA, pB, v, v);

  Eigen7f uA = Eigen7f::Zero();
  uA[0] = 15.0f;

  EXPECT_TRUE(u.isApprox(uA)) << u;
}
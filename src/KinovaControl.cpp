#include "KinovaControl.h"

#include <chrono>
#include <sstream>

#include "KinovaRobot.h"
#include "PD.h"
#include "RobotMath.h"

KinovaControl::KinovaControl(std::string name_,
                             std::shared_ptr<KinovaRobot> robot_,
                             rclcpp::Node::SharedPtr node_)
    : name(name_), robot(robot_), node(node_) {
  std::stringstream s;
  s << name_ << "_pd_controller";
  pdController = std::make_shared<PDController>(s.str());

  node->declare_parameter<bool>(name + "/gravity_compensation", true);
  node->declare_parameter<bool>(name + "/coriolis_compensation", true);
  node->declare_parameter<bool>(name + "/pause", false);
  using namespace std::chrono;

  timer_ =
      node->create_wall_timer(200ms, std::bind(&KinovaControl::respond, this));
  gravity_compensation = true;
  coriolis_compensation = true;
  pause = false;
}

KinovaControl::~KinovaControl() {}

void KinovaControl::respond() {
  bool pause_, gravity_compensation_, coriolis_compensation_;
  pause_ = false;
  this->node->get_parameter(name + "/gravity_compensation",
                            gravity_compensation_);
  this->node->get_parameter(name + "/coriolis_compensation",
                            coriolis_compensation_);
  this->node->get_parameter(name + "/pause",
                            pause_);
  gravity_compensation = gravity_compensation_;
  coriolis_compensation = coriolis_compensation_;
  if (pause_ != pause && pause_) {
    setPause();
  }
  pause = pause_;
}

void KinovaControl::setPause() {
  std::lock_guard<std::mutex> lock(pauseLock);
  pausePose = this->robot->get_pose();
  pauseVelocity = Eigen7f::Zero();
}
std::pair<Eigen7f, Eigen7f> KinovaControl::getPause() {
  std::lock_guard<std::mutex> lock(pauseLock);
  return std::make_pair(pausePose, pauseVelocity);
}

Eigen7f KinovaControl::controller(Eigen7f position, Eigen7f velocity) {
  // auto& clk = *this->node->get_clock();
  // RCLCPP_INFO_STREAM_THROTTLE(rclcpp::get_logger("Runner"), clk, 100,
  // "demand: " << position << " -- actual: "<< this->robot->get_pose() );
  auto u = pdController->calculate(this->robot->get_pose(), position,
                                   this->robot->get_velocity(), velocity);
  if(pause)
  {
    auto [pPose, pVelocity] = getPause();
    u += pdController->calculate(this->robot->get_pose(), pPose,
                                   this->robot->get_velocity(), pVelocity);
  }
  return u;
}

Eigen7f KinovaControl::compensation(Eigen7f u) {
  Eigen7f pose = this->robot->get_pose();
  Eigen7f velocity = robot->get_velocity();

  Eigen::Matrix<float, 7, 7> M;
  Eigen7f C;
  Eigen7f G;

  gravity(pose, G);
  coriolis(pose, velocity, C);

  Eigen7f torque = Eigen7f::Zero();

  torque += u;

  robot->set_command(u);

  if (gravity_compensation) {
    torque += G ;
  }
  if (coriolis_compensation) {
    torque += C;
  }

  return torque;
}

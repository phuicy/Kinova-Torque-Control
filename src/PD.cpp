#include "PD.h"
#include <atomic>
#include <chrono>
#include <functional>

PDController::PDController(std::string name) : Node(name), name(name) {
  std::map<std::string, float> params;
  float default_kp = 10.0f;
  float default_kd = 0.1f;

  Kp = default_kp * Eigen7f::Ones();
  Kd = default_kd * Eigen7f::Ones();

  Kp[4] = 5.0;
  Kp[5] = 5.0;
  Kp[6] = 5.0;
  

  for (int i = 1; i < 8; ++i) {
    params["/joint_" + std::to_string(i) + "/Kp"] = Kp[i-1];
    params["/joint_" + std::to_string(i) + "/Kd"] = Kd[i-1];
  }
  this->declare_parameters(name, params);

  using namespace std::chrono_literals;
  timer_ =
      this->create_wall_timer(500ms, std::bind(&PDController::respond, this));
}

void PDController::respond() {
  std::map<std::string, float> params;
  this->get_parameters(name, params);
  Eigen7f Kp_, Kd_;
  for (int i = 0; i < 7; ++i) {
    Kp_[i] = params["/joint_" + std::to_string(i+1) + "/Kp"];
    Kd_[i] = params["/joint_" + std::to_string(i+1) + "/kd"];
  }
  setKp(Kp_);
  setKd(Kd_);
}

Eigen7f PDController::getKp() {
  std::lock_guard<std::mutex> lock(lock_kp);
  return Kp;
}

Eigen7f PDController::getKd() {
  std::lock_guard<std::mutex> lock(lock_kd);
  return Kd;
}

void PDController::setKp(Eigen7f Kp_) {
  std::lock_guard<std::mutex> lock(lock_kp);
  Kp = std::forward<Eigen7f>(Kp_);
}

void PDController::setKd(Eigen7f Kd_) {
  std::lock_guard<std::mutex> lock(lock_kd);
  // Kd = Kd_;
  Kd = std::forward<Eigen7f>(Kd_);
}

float loop(float x) {
  if (x < -180.0)
    return fmod(x + 360.0f, 360.0f);
  if (x > 180.0)
    return fmod(x - 360.0f, 360.0f);
  return x;
}

Eigen7f PDController::calculate(Eigen7f pActual, Eigen7f pDemand, Eigen7f qActual,
                                Eigen7f qDemand) {
  Eigen7f pDiff = pDemand - pActual;
  auto pD = pDiff.unaryExpr(std::ptr_fun(loop));

  Eigen7f P = getKp().cwiseProduct(pD);
  Eigen7f D = getKd().cwiseProduct(qDemand - qActual);

  return P + D;
}
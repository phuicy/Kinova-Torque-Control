#include "LoopCycle.h"

LoopCycle::LoopCycle(rclcpp::Node::SharedPtr node,
                     std::shared_ptr<KinovaRobot> robot,
                     std::shared_ptr<KinovaControl> robotControl)
    : node(node), local(robot), localControl(robotControl) {}

LoopCycle::LoopCycle(rclcpp::Node::SharedPtr node,
                     std::shared_ptr<KinovaRobot> local,
                     std::shared_ptr<KinovaControl> localControl,
                     std::shared_ptr<KinovaRobot> remote,
                     std::shared_ptr<KinovaControl> remoteControl)
    : node(node), local(local), localControl(localControl), remote(remote),
      remoteControl(remoteControl) {}

LoopCycle::LoopCycle(const LoopCycle &loopCycle)
    : node(loopCycle.node), local(loopCycle.local),
      localControl(loopCycle.localControl), remote(loopCycle.remote),
      remoteControl(loopCycle.remoteControl) {}
LoopCycle::LoopCycle(LoopCycle &&loopCycle)
    : node(loopCycle.node), local(loopCycle.local),
      localControl(loopCycle.localControl), remote(loopCycle.remote),
      remoteControl(loopCycle.remoteControl) {}

std::pair<Eigen7f, Eigen7f> LoopCycle::getDemand() {
  std::lock_guard<std::mutex> lock(demandMutex);
  return std::make_pair(demandPose, demandVelocity);
}

Eigen6f LoopCycle::getTaskDemand() {
  std::lock_guard<std::mutex> lock(demandTaskMutex);
  return demandTask;
}

int64_t GetTickUs() {
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC, &start);

  return (start.tv_sec * 1000000LLU) + (start.tv_nsec / 1000);
}

void LoopCycle::loop() {

  int timer_count = 0;
  int64_t now = 0;
  int64_t last = 0;
  try {
    RCLCPP_INFO(rclcpp::get_logger("Runner"), "Entering Torque mode...");
    this->torqueMode();
    RCLCPP_INFO(rclcpp::get_logger("Runner"), "Entered Torque mode.");

    this->control();
    // Real-time loop
    bool stop;
    node->get_parameter("lateral_run", stop);
    while (!stop) {
      now = GetTickUs();
      auto diff = now - last;
      if (diff > 1000) {
        try {
          this->control();
        } catch (KDetailedException &ex) {
          std::cout << "Kortex exception: " << ex.what() << std::endl;
          std::cout << "Error sub-code: "
                    << SubErrorCodes_Name(SubErrorCodes(
                           (ex.getErrorInfo().getError().error_sub_code())))
                    << std::endl;
        } catch (std::runtime_error &ex2) {
          std::cout << "runtime error: " << ex2.what() << std::endl;
        } catch (...) {
          std::cout << "Unknown error." << std::endl;
        }

        timer_count++;
        last = GetTickUs();
      }
      node->get_parameter("lateral_run", stop);
    }
    RCLCPP_INFO(rclcpp::get_logger("Runner"), "breaking");

    RCLCPP_INFO(rclcpp::get_logger("Runner"), "Entering Position mode...");
    this->positionMode();
    RCLCPP_INFO(rclcpp::get_logger("Runner"), "Entered Position mode.");

  } catch (KDetailedException &ex) {
    std::cout << "API error: " << ex.what() << std::endl;
  } catch (std::runtime_error &ex2) {
    std::cout << "Error: " << ex2.what() << std::endl;
  }
}

void LoopCycle::setDemand(Eigen7f pose, Eigen7f velocity) {
  std::lock_guard<std::mutex> lock(demandMutex);
  demandPose = pose;
  demandVelocity = velocity;
}

void LoopCycle::setTaskDemand(Eigen6f task) {
  std::lock_guard<std::mutex> lock(demandTaskMutex);
  demandTask = task;
}
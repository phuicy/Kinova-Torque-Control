#include "DemandSubscriber.h"
#include "Utils.h"

DemandSubscriber::DemandSubscriber(std::string name, std::string topic,
                                   std::shared_ptr<LoopCycle> loopCycle)
    : Node(name), loopCycle(loopCycle) {
  subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
      topic, 10, std::bind(&DemandSubscriber::topic_callback, this, _1));
}

void DemandSubscriber::topic_callback(
    const sensor_msgs::msg::JointState::SharedPtr msg) const {
  Eigen7f pose, velocity;
  for (unsigned int i = 0; i < actuator_count; ++i) {
      pose[i]     = msg->position[i];
      velocity[i] = msg->velocity[i];
  }
  loopCycle->setDemand(pose,velocity);
}

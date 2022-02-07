#include "TaskSubscriber.h"
#include "Utils.h"

TaskSubscriber::TaskSubscriber(std::string name, std::string topic,
                                   std::shared_ptr<LoopCycle> loopCycle)
    : Node(name), loopCycle(loopCycle) {
  subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
      topic, 10, std::bind(&TaskSubscriber::topic_callback, this, _1));
}

void TaskSubscriber::topic_callback(
    const geometry_msgs::msg::Twist::SharedPtr msg) const {
  Eigen6f task;
  task[0] = msg->linear.x;
  task[1] = msg->linear.y;
  task[2] = msg->linear.z;
  task[3] = msg->angular.x;
  task[4] = msg->angular.y;
  task[5] = msg->angular.z;
  loopCycle->setTaskDemand(task);
}

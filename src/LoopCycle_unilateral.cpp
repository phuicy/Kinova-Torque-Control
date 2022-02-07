#include "LoopCycle.h"

void LoopCycle::control()
{
  auto [pose, velocity] = getDemand();
  Eigen7f u = localControl->controller( pose, velocity);
  Eigen7f torque = localControl->compensation(u);
  local->set(torque);
}

void LoopCycle::torqueMode()
{
	local->torqueMode();
}

void LoopCycle::positionMode()
{
	local->positionMode();
}
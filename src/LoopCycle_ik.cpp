#include "LoopCycle.h"
#include "Math/InverseKinematics.h"

void LoopCycle::control()
{
  auto pose = local->get_pose();
  Eigen7f qp = Eigen7f::Zero();
  Eigen6f xp = getTaskDemand();

  inverse_kinematics(pose,
                      xp,
                      qp);

  Eigen7f u = localControl->controller( pose, qp);
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
#pragma once

#include "SpaceshipController.h"

SpaceshipController::SpaceshipController(unsigned new_CTRL_LEFT, unsigned new_CTRL_RIGHT,
										 unsigned new_CTRL_FORWARD, unsigned new_CTRL_BACKWARD,
										 unsigned new_CTRL_MOVEMENT_BREAK, unsigned new_CTRL_ROTATION_BREAK)
{
	CTRL_LEFT = new_CTRL_LEFT;
	CTRL_RIGHT = new_CTRL_RIGHT;

	CTRL_FORWARD = new_CTRL_FORWARD;
	CTRL_BACKWARD = new_CTRL_BACKWARD;

	CTRL_MOVEMENT_BREAK = new_CTRL_MOVEMENT_BREAK;
	CTRL_ROTATION_BREAK = new_CTRL_ROTATION_BREAK;
}

void SpaceshipController::update(SpaceshipLocomotion &spaceshipLocomotion)
{
	// Turning
	if (sfw::getKey(CTRL_LEFT))
	{
		spaceshipLocomotion.doTurn(1);
	}
	if (sfw::getKey(CTRL_RIGHT))
	{
		spaceshipLocomotion.doTurn(-1);
	}

	// Thrust
	if (sfw::getKey(CTRL_FORWARD))
	{
		spaceshipLocomotion.doThrust(1);
	}
	if (sfw::getKey(CTRL_BACKWARD))
	{
		spaceshipLocomotion.doThrust(-1);
	}

	// Breaking
	if (sfw::getKey(CTRL_MOVEMENT_BREAK))
	{
		spaceshipLocomotion.doBreakMovement(1);
	}
	if (sfw::getKey(CTRL_ROTATION_BREAK))
	{
		spaceshipLocomotion.doBreakRotate(1);
	}
}
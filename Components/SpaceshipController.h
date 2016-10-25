#pragma once

#include "SpaceshipLocomotion.h"

class SpaceshipController
{
public:
	unsigned CTRL_LEFT, CTRL_RIGHT, 
		CTRL_FORWARD, CTRL_BACKWARD, 
		CTRL_MOVEMENT_BREAK, CTRL_ROTATION_BREAK;

	SpaceshipController(unsigned new_CTRL_LEFT = 'A', unsigned new_CTRL_RIGHT = 'D', 
						unsigned new_CTRL_FORWARD = 'W', unsigned new_CTRL_BACKWARD = 'S', 
						unsigned new_CTRL_MOVEMENT_BREAK = 'Q', unsigned new_CTRL_ROTATION_BREAK = 'E');

	void update(SpaceshipLocomotion &spaceshipLocomotion);
};
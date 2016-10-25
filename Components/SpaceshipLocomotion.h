#pragma once

#include "RigidBody.h"
#include "Transform.h"
#include "sfwdraw.h"
#include <iostream>

class SpaceshipLocomotion
{
	float vertThrust, horizThrust,
			speed, maxThrust,
			vertBreak, horzBreak;

	float turn, turnSpeed, maxTurnSpeed,
			vertBreakAmount, horzBreakAmount;

public:
	SpaceshipLocomotion();

	void doThrust(float addVertThrust);
	void doTurn(float addHorzThrust);
	void doBreakMovement(float addBreakMovement);
	void doBreakRotate(float addBreakRotate);

	void update(Transform & trans, RigidBody & rig);
};
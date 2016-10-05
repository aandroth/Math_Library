#pragma once

#include "RigidBody.h"
#include "sfwdraw.h"
#include <iostream>

class SpaceshipLocomotion
{
	float vertThrust, horizThrust;
	float speed, maxThrust;

	float turn, turnSpeed, maxTurnSpeed;

public:
	SpaceshipLocomotion();

	void doThrust();

	void doTurn();

	void update(RigidBody & rig, float deltaTime);
};
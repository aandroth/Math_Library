#pragma once
#include "SpaceshipLocomotion.h"

SpaceshipLocomotion::SpaceshipLocomotion()
{
	vertThrust = 0.0;
	horizThrust = 0.0;
	speed = 100.0;
	maxThrust = 100.0;

	turn = 0;
	turnSpeed = 0.5;
	maxTurnSpeed = 100.0;
}

void SpaceshipLocomotion::doThrust()
{
	if (sfw::getKey('W') && vertThrust < maxThrust)
		vertThrust += speed;
	else if (sfw::getKey('S') && vertThrust > -maxThrust)
		vertThrust -= speed;
}

void SpaceshipLocomotion::doTurn()
{
	if (sfw::getKey('A') && horizThrust < maxThrust)
		horizThrust += speed;
	else if (sfw::getKey('D') && horizThrust > -maxThrust)
		horizThrust -= speed;
}

void SpaceshipLocomotion::update(RigidBody & rig, float deltaTime)
{
	doThrust();
	doTurn();

	//std::cout << vertThrust << std::endl;
	rig.accelleration.y = vertThrust;
	rig.angularAccelleration = horizThrust;

	vertThrust = 0;
	horizThrust = 0;
}
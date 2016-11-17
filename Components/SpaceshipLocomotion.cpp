#include "SpaceshipLocomotion.h"

SpaceshipLocomotion::SpaceshipLocomotion()
{
	vertThrust = 0.0;
	horizThrust = 0.0;
	speed = 500.0;
	maxThrust = 100.0;

	turn = 0;
	turnSpeed = 50;
	maxTurnSpeed = 30.0;

	vertBreak = 0.0;
	horzBreak = 0.0;
	vertBreakAmount = 1;
	horzBreakAmount = 1;
}

void SpaceshipLocomotion::doThrust(float addVertThrust)
{
	vertThrust += speed*addVertThrust;
}

void SpaceshipLocomotion::doTurn(float addHorzThrust)
{
	horizThrust += turnSpeed*addHorzThrust;
}

void SpaceshipLocomotion::doBreakMovement(float addBreakMovement)
{
	vertBreak = addBreakMovement;
}

void SpaceshipLocomotion::doBreakRotate(float addBreakRotate)
{
	horzBreak = addBreakRotate;
}

void SpaceshipLocomotion::update(Transform & trans, RigidBody & rig)
{
	rig.addForce(Vec2(vertThrust*trans.getDirection().x,
					  vertThrust*trans.getDirection().y));
	rig.addForce((rig.getVelocity() * -1 * vertBreakAmount)*vertBreak);

	rig.addTorque(horizThrust);
	rig.addTorque(horzBreak*(-rig.angularVelocity*horzBreakAmount));


	vertThrust = horizThrust = 0.0;
	vertBreak = horzBreak = 0.0;
}
#include "RigidBody.h"

void RigidBody::integrate(Transform &trans, const float deltaTime)
{
	velocity = accelleration * deltaTime * 100;
	angularVelocity = angularAccelleration * deltaTime * 100;

	trans.position.x = trans.position.x + velocity.y * cos(degreesToRadians(trans.facing)) * deltaTime;
	trans.position.y = trans.position.y + velocity.y * sin(degreesToRadians(trans.facing)) * deltaTime;
	//trans.facing = trans.facing + angularVelocity * deltaTime;
}

void RigidBody::setAccelleration(Vec2 newAcc)
{
	accelleration = newAcc;
}

Vec2 RigidBody::getAccelleration() const
{
	return accelleration;
}

void RigidBody::setVelocity(Vec2 newVel)
{
	velocity = newVel;
}

Vec2 RigidBody::getVelocity() const
{
	return velocity;
}
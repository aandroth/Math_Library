#include "RigidBody.h"

RigidBody::RigidBody()
{
	mass = 1.0;
	torque = 0;
	force = Vec2(0, 0);
	impulse = Vec2(0, 0);
	velocity = Vec2(0, 0);
	accelleration = Vec2(0, 0);
	angularVelocity = 0;
	angularAccelleration = 0;
}

void RigidBody::addForce(const Vec2 & a_force)
{
	force += a_force;
}
void RigidBody::addImpulse(const Vec2 & an_impulse)
{
	impulse += an_impulse;
}

void RigidBody::addTorque(float a_torque)
{
	torque += a_torque;
}

void RigidBody::integrate(Transform &trans, const float deltaTime)
{
	accelleration = force / mass;
	velocity += accelleration * deltaTime + impulse/mass;
	trans.m_position += velocity * deltaTime;
	force = impulse = { 0, 0 };

	angularAccelleration = torque / mass;
	angularVelocity += angularAccelleration * deltaTime;
	trans.m_facing += angularVelocity * deltaTime;
	torque = 0;
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

void RigidBody::debugDraw(const Mat3 &T, const Transform & trans)
{
	Vec2 pos = Vec2((T * trans.getGlobalTransform()).z1, (T * trans.getGlobalTransform()).z2);
	Vec2 vel = pos + velocity;
	Vec2 acc = accelleration + pos;

	sfw::drawLine(pos.x, pos.y,
		vel.x, vel.y, CYAN);

	sfw::drawLine(pos.x, pos.y,
		acc.x, acc.y, MAGENTA);
}
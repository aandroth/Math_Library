#pragma once

#include "Test.h"
#include "Transform.h"
#include "sfwdraw.h"
#include <iostream>

class RigidBody
{
public:
	Vec2 velocity, accelleration;
	float angularVelocity = 0, angularAccelleration;

	void integrate(Transform &trans, const float deltaTime);

	void setAccelleration(Vec2);
	Vec2 getAccelleration() const;

	void setVelocity(Vec2);
	Vec2 getVelocity() const;
};


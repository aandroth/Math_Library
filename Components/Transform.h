#pragma once

#include "Test.h"
#include "sfwdraw.h"

class Transform
{
public:
	Vec2 position;
	Vec2 scale;
	float facing;

	Transform();

	Vec2 getDirection();
	void setDirection(const Vec2 &dir);

	void debugDraw();
};

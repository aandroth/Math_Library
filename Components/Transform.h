#pragma once

#include "Test.h"
#include "sfwdraw.h"

class Transform
{
	Vec2 position;
	Vec2 scale;
	float facing;

	Vec2 getDirection();
	void setDirection(const Vec2 &dir);

	void debugDraw();
};

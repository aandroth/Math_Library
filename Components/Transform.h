#pragma once

#include "Test.h"
#include "sfwdraw.h"
#include "Mat3.h"

class Transform
{
public:
	Vec2 m_position;
	Vec2 m_scale;
	float m_facing;
	Transform * m_parent;

	Transform(float x = 0, float y = 0, float w = 1, float h = 1, float a = 0);

	Vec2 getUp() const;
	Vec2 getDirection() const;
	void setDirection(const Vec2 &dir);

	Mat3 getLocalTransform() const;
	Mat3 getGlobalTransform() const;

	void debugDraw(const Mat3 &T = mat3Identity()) const;

};


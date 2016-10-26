#pragma once
#include <cmath>
#include "Shapes.h"

float minf(const float &f0, const float &f1)
{
	if (f0 < f1)
		return f0;

	return f1;
}

struct CollisionData1D
{
	float m_penetrationDepth;
	float m_collisionNormal; // Will be 1 or -1

	bool resultIsCollision() const;
	float MTV() const;
};

CollisionData1D collisionDetection1D(float Amin, float Amax, 
									 float Bmin, float Bmax);

CollisionData1D collisionDetection1D(float Amin, float Amax, float Adelta,
									 float Bmin, float Bmax, float Bdelta);

struct CollisionData2D
{
	float m_penetrationDepth;
	Vec2 m_collisionNormal;

	bool resultIsCollision() const;
	Vec2 MTV() const;
};

CollisionData2D boxCollision(const AABB &A,
							const AABB &B);
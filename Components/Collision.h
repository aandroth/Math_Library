#pragma once
#include <cmath>
#include "Shapes.h"

//float minf(const float &f0, const float &f1)
//{
//	if (f0 < f1)
//		return f0;
//
//	return f1;
//}

struct CollisionData1D
{
	float m_penetrationDepth;
	float m_collisionNormal; // Will be 1 or -1

	bool resultIsCollision() const;
	float MTV() const;
};

CollisionData1D collisionDetection1D(float Amin, float Amax, 
									 float Bmin, float Bmax);


struct CollisionData1DSwept
{
	float m_entryTime, m_exitTime;
	float m_collisionNormal; // Will be 1 or -1
};

CollisionData1DSwept collisionDetection1DSwept(float Amin, float Amax,
											   float Bmin, float Bmax, 
											   float Avel, float Bvel);

struct CollisionData2D
{
	float m_penetrationDepth;
	Vec2 m_collisionNormal;

	bool resultIsCollision() const;
	Vec2 MTV() const;
};

struct CollisionData2DSwept
{
	float m_entryTime, m_exitTime;
	Vec2 m_collisionNormal;

	bool resultIsCollision(const AABB &A, const AABB &B) const;
};

CollisionData2D boxCollision(const AABB &A,
	const AABB &B);

CollisionData2D planeBoxCollision(const Plane &P,
								  const AABB &B);

CollisionData2DSwept planeBoxCollisionSwept(const Plane &P,
											const Vec2 &pVel,
											const AABB  &aabb);
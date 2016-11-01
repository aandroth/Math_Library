#include "Collision.h"
#include <iostream>
using std::cout;

bool CollisionData1D::resultIsCollision() const
{
	return (m_penetrationDepth >= 0);
}

float CollisionData1D::MTV() const
{
	return m_penetrationDepth * m_collisionNormal;
}


CollisionData1D collisionDetection1D(float Amin, float Amax, 
									 float Bmin, float Bmax)
{
	CollisionData1D collisionDataDetection;

	float tl = Amax - Bmin, tr = Bmax - Amin;

	 if (tl < tr)
	 {
		 collisionDataDetection.m_penetrationDepth = tl;
		 collisionDataDetection.m_collisionNormal = -1;
	 }
	 else
	 {
		 collisionDataDetection.m_penetrationDepth = tr;
		 collisionDataDetection.m_collisionNormal = 1;
	 }

	return collisionDataDetection;
}

CollisionData1DSwept collisionDetection1DSwept(float Amin, float Amax,
											   float Bmin, float Bmax, 
											   float Avel, float Bvel)
{
	CollisionData1DSwept collisionDataDetectionSwept;

	float tl = (Amin - Bmax) / (Bvel - Avel),
		  tr = (Bmin - Amax) / (Avel - Bvel);

	collisionDataDetectionSwept.m_entryTime = fmin(tl, tr);
	collisionDataDetectionSwept.m_exitTime =  fmax(tl, tr);

	collisionDataDetectionSwept.m_collisionNormal = copysignf(1, tl - tr);

	return collisionDataDetectionSwept;
}

bool CollisionData2D::resultIsCollision() const
{
	return (m_penetrationDepth >= 0);
}

Vec2 CollisionData2D::MTV() const
{
	return m_collisionNormal * m_penetrationDepth;
}

CollisionData2D boxCollision(const AABB &A,
						     const AABB &B)
{
	CollisionData2D retVal;

	CollisionData1D collisionX = collisionDetection1D(A.min().x, A.max().x, B.min().x, B.max().x), 
					collisionY = collisionDetection1D(A.min().y, A.max().y, B.min().y, B.max().y);

	Vec2 axisOfPenetration;

	if (collisionX.MTV() < collisionY.MTV())
	{
		retVal.m_penetrationDepth = collisionX.m_penetrationDepth;
		retVal.m_collisionNormal = Vec2(1, 0) * collisionX.m_collisionNormal;
	}
	else// (collisionX.MTV() >= collisionY.MTV())
	{
		retVal.m_penetrationDepth = collisionY.m_penetrationDepth;
		retVal.m_collisionNormal = Vec2(1, 0) * collisionY.m_collisionNormal;
	}

	return retVal;
}


bool CollisionData2DSwept::resultIsCollision(const AABB &A, const AABB &B) const
{
	CollisionData2DSwept retVal;

	CollisionData1DSwept collisionX = collisionDetection1DSwept(A.min().x, A.max().x, B.min().x, B.max().x, A.m_vel.x, B.m_vel.x),
						 collisionY = collisionDetection1DSwept(A.min().y, A.max().y, B.min().y, B.max().y, A.m_vel.y, B.m_vel.y);

	if (collisionX.m_entryTime > collisionX.m_exitTime ||
		collisionY.m_entryTime > collisionY.m_exitTime)
	{
		return true;
	}

	return false;
}

CollisionData2D planeBoxCollision(const Plane &P,
								  const AABB  &aabb)
{
	// find the projection of a point onto the axis of the plane's normal by using the dot product
	Vec2 Bmin(INFINITY,   INFINITY),
		 Bmax(-INFINITY, -INFINITY);

	Vec2 vecArr[4];

	vecArr[0] = Vec2(aabb.m_pos.x - aabb.m_he.x, aabb.m_pos.y - aabb.m_he.y); // br
	vecArr[1] = Vec2(aabb.m_pos.x - aabb.m_he.x, aabb.m_pos.y + aabb.m_he.y); // tr
	vecArr[2] = Vec2(aabb.m_pos.x + aabb.m_he.x, aabb.m_pos.y + aabb.m_he.y); // tl
	vecArr[3] = Vec2(aabb.m_pos.x + aabb.m_he.x, aabb.m_pos.y - aabb.m_he.y); // bl

	float max = -INFINITY, min = INFINITY;
	Vec2 maxVec, minVec;

	for (int ii = 0; ii < 4; ++ii)
	{
		if (max < dot(vecArr[ii] - P.m_position, perp(P.m_direction)))
		{
			max = dot(vecArr[ii] - P.m_position, perp(P.m_direction));
			maxVec = vecArr[ii];
		}
		if(min > dot(vecArr[ii] - P.m_position, perp(P.m_direction)))
		{
			min = dot(vecArr[ii] - P.m_position, perp(P.m_direction));
			minVec = vecArr[ii];
		}
	}

	CollisionData1D collision = collisionDetection1D(minVec.x, minVec.y, maxVec.x, maxVec.y);

	CollisionData2D retVal;

	retVal.m_penetrationDepth = collision.m_penetrationDepth;
	retVal.m_collisionNormal = Vec2(1, 0) * collision.m_collisionNormal;

	return retVal();

}
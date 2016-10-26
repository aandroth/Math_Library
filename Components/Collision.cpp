#include "Collision.h"

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
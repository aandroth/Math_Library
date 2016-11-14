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

	float tl = Bmax - Amin, tr = Amax - Bmin;

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

CollisionData2D planeAABBCollision(const Plane &P,
								  const AABB  &aabb)
{
	float pTL = dot(P.m_direction, Vec2(aabb.min().x, aabb.max().y));
	float pBR = dot(P.m_direction, Vec2(aabb.max().x, aabb.min().y));
	float pTR = dot(P.m_direction, aabb.min());
	float pBL = dot(P.m_direction, aabb.max());

	float pBmin = fminf(fminf(pTR, pTL), fminf(pBR, pBL));
	float pPmax = dot(P.m_direction, P.m_position);

	CollisionData2D retVal;

	retVal.m_penetrationDepth = pPmax - pBmin;
	retVal.m_collisionNormal = P.m_direction;

	return retVal;
}

CollisionData2DSwept planeAABBCollisionSwept(const Plane &P,
											const AABB  &aabb,
											const Vec2  &pVel)
{
	float pTL = dot(P.m_direction, Vec2(aabb.min().x, aabb.max().y));
	float pBR = dot(P.m_direction, Vec2(aabb.max().x, aabb.min().y));
	float pTR = dot(P.m_direction, aabb.min());
	float pBL = dot(P.m_direction, aabb.max());

	float pPmax = dot(P.m_direction, P.m_position);
	float pBmin = (fminf(fminf(pTR, pTL), fminf(pBR, pBL)) - pPmax) / dot(P.m_direction, pVel);
	float pBmax = (fmaxf(fmaxf(pTR, pTL), fmaxf(pBR, pBL)) - pPmax) / dot(P.m_direction, pVel);

	CollisionData2DSwept retVal;

	retVal.m_entryTime = pPmax - pBmin;
	retVal.m_exitTime  = pPmax - pBmax;
	retVal.m_collisionNormal = P.m_direction;


	return retVal;
}

/*
CollisionData2D HullCollision(const Hull &Hull_0, const Hull &Hull_1)
{
	CollisionData2D currColl, bestColl;

	Hull *leastSidesHull, *mostSidesHull;

	float maxPenetrationDepth = -INFINITY;

	if (Hull_0.m_size < Hull_1.m_size)
	{
		*leastSidesHull = Hull_0;
		*mostSidesHull = Hull_1;
	}
	else
	{
		*leastSidesHull = Hull_1;
		*mostSidesHull = Hull_0;
	}

	for (int ii = 0; ii < leastSidesHull->m_size; ++ii)
	{
		float min = INFINITY; // , max = -INFINITY;
		bool pointIsWithinHull = true;
		// Get the min and max of the other hull's points on that normal vector
		for (int jj = 0; jj < mostSidesHull->m_size; ++jj)
		{
			float pointAlongNormal = dot(leastSidesHull->m_normals[ii], mostSidesHull->m_vertArray[jj]);

			// Check if all points have no gaps between them
			min > pointAlongNormal ? pointAlongNormal : min;
			//max < pointAlongNormal ? pointAlongNormal : max;
		}

		float pointAlongNormal = dot(leastSidesHull->m_normals[ii], leastSidesHull->m_vertArray[ii]);
		if (currColl.m_penetrationDepth < (pointAlongNormal - min))
		{
			maxPenetrationDepth = pointAlongNormal - min;
			bestColl = currColl;
		}
	}

	bestColl.m_penetrationDepth = maxPenetrationDepth;
}
*/

CollisionData1D HullCollision(const Hull &Hull_0, const Hull &Hull_1)
{
	CollisionData1D currColl, bestColl;
	bestColl.m_penetrationDepth = INFINITY;
	float maxPenetrationDepth = -INFINITY;

	Vec2 allNormalsArr[32];

	for (int ii = 0; ii < Hull_0.m_size; ++ii)
	{
		allNormalsArr[ii] = Hull_0.m_normals[ii];
	}	
	for (int ii = Hull_0.m_size, jj = 0; jj < Hull_1.m_size; ++ii, ++jj)
	{
		allNormalsArr[ii] = Hull_1.m_normals[jj];
	}

	for (int ii = 0; ii < Hull_0.m_size + Hull_1.m_size; ++ii)
	{
		float aMin = INFINITY, aMax = -INFINITY, bMin = INFINITY, bMax = -INFINITY; 
		for (int jj = 0; jj < Hull_0.m_size; ++jj)
		{
			float dotProduct_0 = dot(allNormalsArr[ii], Hull_0.m_vertArray[jj]);
			aMin > dotProduct_0 ? dotProduct_0 : aMin;
			aMax < dotProduct_0 ? dotProduct_0 : aMax;
		}
		for (int jj = 0; jj < Hull_1.m_size; ++jj)
		{
			float dotProduct_1 = dot(allNormalsArr[ii], Hull_1.m_vertArray[jj]);
			bMin > dotProduct_1 ? dotProduct_1 : bMin;
			bMax < dotProduct_1 ? dotProduct_1 : bMax;
		}

		currColl = collisionDetection1D(aMin, aMax, bMin, bMax);
		if (bestColl.m_penetrationDepth > currColl.m_penetrationDepth)
		{
			bestColl = currColl;
		}
	}
	return bestColl;
}

CollisionData1DSwept HullCollisionSwept(const Hull &Hull_0, const Hull &Hull_1, const Vec2 Vel_0, const Vec2 Vel_1)
{
	CollisionData1DSwept currColl, bestColl;
	bestColl.m_entryTime = INFINITY;
	float maxPenetrationDepth = -INFINITY;

	Vec2 allNormalsArr[32];

	for (int ii = 0; ii < Hull_0.m_size; ++ii)
	{
		allNormalsArr[ii] = Hull_0.m_normals[ii];
	}
	for (int ii = Hull_0.m_size, jj = 0; jj < Hull_1.m_size; ++ii, ++jj)
	{
		allNormalsArr[ii] = Hull_1.m_normals[jj];
	}

	for (int ii = 0; ii < Hull_0.m_size + Hull_1.m_size; ++ii)
	{
		float aMin = INFINITY, aMax = -INFINITY, bMin = INFINITY, bMax = -INFINITY;
		for (int jj = 0; jj < Hull_0.m_size; ++jj)
		{
			float dotProduct_0 = dot(allNormalsArr[ii], Hull_0.m_vertArray[jj]);
			aMin > dotProduct_0 ? dotProduct_0 : aMin;
			aMax < dotProduct_0 ? dotProduct_0 : aMax;
		}
		for (int jj = 0; jj < Hull_1.m_size; ++jj)
		{
			float dotProduct_1 = dot(allNormalsArr[ii], Hull_1.m_vertArray[jj]);
			bMin > dotProduct_1 ? dotProduct_1 : bMin;
			bMax < dotProduct_1 ? dotProduct_1 : bMax;
		}

		currColl = collisionDetection1DSwept(aMin, aMax, bMin, bMax, dot(allNormalsArr[ii], Vel_0), dot(allNormalsArr[ii], Vel_1));
		if (bestColl.m_entryTime > currColl.m_entryTime)
		{
			bestColl = currColl;
		}
	}
	return bestColl;
}
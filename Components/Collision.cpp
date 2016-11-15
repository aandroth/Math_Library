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
		 collisionDataDetection.m_collisionNormal  = -1;
	 }
	 else
	 {
		 collisionDataDetection.m_penetrationDepth = tr;
		 collisionDataDetection.m_collisionNormal  = 1;
	 }

	return collisionDataDetection;
}

CollisionDataSwept1D collisionDetectionSwept1D(float Amin, float Amax,
											   float Bmin, float Bmax, 
											   float Avel, float Bvel)
{
	CollisionDataSwept1D collisionDataDetectionSwept;

	float tl = (Amin - Bmax) / (Bvel - Avel),
		  tr = (Bmin - Amax) / (Avel - Bvel);

	collisionDataDetectionSwept.m_entryTime = fmin(tl, tr);
	collisionDataDetectionSwept.m_exitTime =  fmax(tl, tr);

	collisionDataDetectionSwept.m_collisionNormal = copysignf(1, tl - tr);

	return collisionDataDetectionSwept;
}

bool CollisionData::resultIsCollision() const
{
	return (m_penetrationDepth >= 0);
}

Vec2 CollisionData::MTV() const
{
	return m_collisionNormal * m_penetrationDepth;
}

CollisionData aabbCollision(const AABB &A,
	const AABB &B)
{
	CollisionData retVal;

	CollisionData1D collisionX = collisionDetection1D(A.min().x, A.max().x, B.min().x, B.max().x),
		collisionY = collisionDetection1D(A.min().y, A.max().y, B.min().y, B.max().y);

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


CollisionDataSwept aabbCollisionSwept(const AABB &A, Vec2 A_vel,
									  const AABB &B, Vec2 B_vel)
{
	CollisionDataSwept retVal;


	CollisionData1D collisionX = collisionDetection1D(A.min().x, A.max().x, B.min().x, B.max().x),
					collisionY = collisionDetection1D(A.min().y, A.max().y, B.min().y, B.max().y);

	CollisionDataSwept1D collisionX_swept = collisionDetectionSwept1D(A.min().x, A.max().x, B.min().x, B.max().x, A_vel.x, B_vel.x),
						 collisionY_swept = collisionDetectionSwept1D(A.min().y, A.max().y, B.min().y, B.max().y, A_vel.y, B_vel.y);



	if (collisionX.MTV() < collisionY.MTV())
	{
		retVal.m_entryTime = collisionX.m_penetrationDepth;
		retVal.m_collisionNormal = Vec2(1, 0) * collisionX.m_collisionNormal;
	}
	else// (collisionX.MTV() >= collisionY.MTV())
	{
		retVal.m_penetrationDepth = collisionY.m_penetrationDepth;
		retVal.m_collisionNormal = Vec2(1, 0) * collisionY.m_collisionNormal;
	}

	return retVal;
}


bool CollisionDataSwept::resultIsCollision(const AABB &A, const AABB &B) const
{
	CollisionDataSwept retVal;

	CollisionDataSwept1D collisionX = collisionDetectionSwept1D(A.min().x, A.max().x, B.min().x, B.max().x, A.m_vel.x, B.m_vel.x),
						 collisionY = collisionDetectionSwept1D(A.min().y, A.max().y, B.min().y, B.max().y, A.m_vel.y, B.m_vel.y);

	if (collisionX.m_entryTime > collisionX.m_exitTime ||
		collisionY.m_entryTime > collisionY.m_exitTime)
	{
		return true;
	}

	return false;
}

CollisionData planeAABBCollision(const Plane &P,
								  const AABB  &aabb)
{
	float pTL = dot(P.m_direction, Vec2(aabb.min().x, aabb.max().y));
	float pBR = dot(P.m_direction, Vec2(aabb.max().x, aabb.min().y));
	float pTR = dot(P.m_direction, aabb.min());
	float pBL = dot(P.m_direction, aabb.max());

	float pBmin = fminf(fminf(pTR, pTL), fminf(pBR, pBL));
	float pPmax = dot(P.m_direction, P.m_position);

	CollisionData retVal;

	retVal.m_penetrationDepth = pPmax - pBmin;
	retVal.m_collisionNormal = P.m_direction;

	return retVal;
}

CollisionDataSwept planeAABBCollisionSwept(const Plane &P,
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

	CollisionDataSwept retVal;

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

CollisionData HullCollision(const Hull &Hull_0, const Hull &Hull_1)
{
	CollisionData bestColl;
	bestColl.m_penetrationDepth = INFINITY;

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
		float aMin = INFINITY, aMax = -INFINITY, 
			  bMin = INFINITY, bMax = -INFINITY; 

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

		float pDr, pDl, pD, Dir;
		pDr = aMax - bMin;
		pDl = bMax - aMin;

		pD = fminf(pDr, pDl);

		Dir = copysignf(1, pDl - pDr);

		if (pD < bestColl.m_penetrationDepth)
		{
			bestColl.m_penetrationDepth = pD;
			bestColl.m_collisionNormal = allNormalsArr[ii] * Dir;
		}
	}
	return bestColl;
}

CollisionDataSwept HullCollisionSwept(const Hull &Hull_0, const Hull &Hull_1, const Vec2 Vel_0, const Vec2 Vel_1)
{
	CollisionDataSwept bestColl;
	bestColl.m_entryTime = INFINITY;
	bestColl.m_exitTime = -INFINITY;

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
		float aMin = INFINITY, aMax = -INFINITY,
			  bMin = INFINITY, bMax = -INFINITY;

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

		float pDr, pDl, pD, H;
		pDr = aMax - bMin;
		pDl = bMax - aMin;

		pD = fminf(pDr, pDl);

		H = copysignf(1, pDl - pDr);

		if (pD < bestColl.m_entryTime)
		{
			bestColl.m_entryTime = pD;
			bestColl.m_collisionNormal = allNormalsArr[ii] * H;
		}
	}
	return bestColl;
}

// NOT COMPLETE /////////////////////////////////////////////////////////
CollisionData StaticResolution(Transform & TA, RigidBody & RA, Collider CA,
								Transform & TB, Collider CB)
{
	CollisionData collData = ColliderCollision(TA, CA, TB, CB);

	return collData;
}

CollisionData DynamicResolution(Transform & TA, RigidBody & RA, Collider CA,
								Transform & TB, RigidBody & RB, Collider CB, float bounciness)
{
	CollisionData collData = ColliderCollision(TA, CA, TB, CB);

	Vec2 A_initVel = RA.getVelocity(), A_finVel,
		 B_initVel = RB.getVelocity(), B_finVel;

	float  A_mass = RA.mass, B_mass = RB.mass, bounce = bounciness;

	if (collData.resultIsCollision())
	{
		Vec2 MTV = collData.m_collisionNormal * collData.m_penetrationDepth;

		float am = magnitude(RA.velocity * RA.mass),
			  bm = magnitude(RB.velocity * RB.mass),
			  cm = am + bm;

		TA.m_position -= MTV * (1- (am / cm));
		TB.m_position += MTV * (1- (bm / cm));

		A_finVel = (A_initVel * A_mass + B_initVel * B_mass + ((A_initVel - B_initVel) * -bounce) * B_mass / (A_mass * B_mass));

		B_finVel = ((A_initVel - B_initVel) * bounce) + A_finVel;

		RA.velocity = A_finVel;
		RB.velocity = B_finVel;
	}

	return collData;
}
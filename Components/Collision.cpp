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

	float tl = Bmax - Amin, 
		  tr = Amax - Bmin;

	cout << "Amin: " << Amin << ", Amax: " << Amax << "\n";
	cout << "Bmin: " << Bmin << ", Bmax: " << Bmax << "\n";
	cout << "tl: " << tl << ", tr: " << tr << "\n";


	 //if (tl < tr)
	 //{
		// collisionDataDetection.m_penetrationDepth = tl;
		// collisionDataDetection.m_collisionNormal  = -1;
	 //}
	 //else
	 //{
		// collisionDataDetection.m_penetrationDepth = tr;
		// collisionDataDetection.m_collisionNormal  = 1;
	 //}

	collisionDataDetection.m_penetrationDepth = fmin(tl, tr);

	//if(tl > tr)
		collisionDataDetection.m_collisionNormal = copysignf(1, tl - tr);
	//else
	//	collisionDataDetection.m_collisionNormal = copysignf(1, tr - tl);

	cout << "m_collisionNormal: " << collisionDataDetection.m_collisionNormal << "\n";

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

	cout << "collisionX: " << "\n";
	CollisionData1D collisionX = collisionDetection1D(A.min().x, A.max().x, B.min().x, B.max().x);
	cout << "collisionY: " << "\n";
	CollisionData1D	collisionY = collisionDetection1D(A.min().y, A.max().y, B.min().y, B.max().y);

	if (collisionX.MTV() < collisionY.MTV())
	{
		retVal.m_penetrationDepth = collisionX.m_penetrationDepth;
		retVal.m_collisionNormal = Vec2(1, 0) * collisionX.m_collisionNormal;
		cout << "Collision along X " << "\n";
	}
	else// (collisionX.MTV() >= collisionY.MTV())
	{
		retVal.m_penetrationDepth = collisionY.m_penetrationDepth;
		retVal.m_collisionNormal = Vec2(0, 1) * collisionY.m_collisionNormal;
		cout << "Collision along Y " << "\n";
	}
	cout << "collisionX.MTV(): " << collisionX.MTV() << "\n";
	cout << "collisionY.MTV(): " << collisionY.MTV() << "\n";
	cout << "\n\n";

	return retVal;
}


CollisionDataSwept aabbCollisionSwept(const AABB &A, Vec2 A_vel,
									  const AABB &B, Vec2 B_vel)
{
	CollisionDataSwept retVal;

	// In case the objects have no velocity
	CollisionData1D collisionX = collisionDetection1D(A.min().x, A.max().x, B.min().x, B.max().x),
					collisionY = collisionDetection1D(A.min().y, A.max().y, B.min().y, B.max().y);

	// Swept results
	CollisionDataSwept1D collisionX_swept = collisionDetectionSwept1D(A.min().x, A.max().x, B.min().x, B.max().x, A_vel.x, B_vel.x),
						 collisionY_swept = collisionDetectionSwept1D(A.min().y, A.max().y, B.min().y, B.max().y, A_vel.y, B_vel.y);

	bool xSwept = ((A_vel.x - B_vel.x) != 0);
	bool ySwept = ((A_vel.y - B_vel.y) != 0);

	if (collisionY_swept.m_entryTime < collisionX_swept.m_entryTime || xSwept && !ySwept)
	{
		retVal.m_collisionNormal = Vec2(1, 0) * collisionX_swept.m_collisionNormal;
		retVal.m_entryTime = collisionX_swept.m_entryTime;


		retVal.collides = ySwept || collisionY.resultIsCollision();
	}
	else if (ySwept) // collisionY_swept.m_entryTime >= collisionX_swept.m_entryTime
	{
		retVal.m_collisionNormal = Vec2(0, 1) * collisionY_swept.m_collisionNormal;
		retVal.m_entryTime = collisionY_swept.m_entryTime;

		//cout << xSwept << ", " << collisionX.resultIsCollision() << "\n\n";

		retVal.collides = xSwept || collisionX.resultIsCollision();
	}

	if (collisionY_swept.m_exitTime < collisionX_swept.m_exitTime || ySwept && !xSwept)
	{
		retVal.m_exitTime = collisionY_swept.m_exitTime;
	}
	else if (xSwept) // collisionY_swept.m_exitTime >= collisionX_swept.m_exitTime
	{
		retVal.m_exitTime = collisionX_swept.m_exitTime;
	}

	return retVal;
}


bool CollisionDataSwept::resultIsCollision() const
{
	return m_entryTime >= 0 && m_entryTime <= 1;
	//return m_entryTime < m_exitTime;
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

CollisionDataSwept planeAABBCollisionSwept(const Plane &P, const Vec2  &pVel,
											const AABB  &aabb, const Vec2  &bVel)
{
	

	float pTL = dot(P.m_direction, Vec2(aabb.min().x, aabb.max().y));
	float pBR = dot(P.m_direction, Vec2(aabb.max().x, aabb.min().y));
	float pTR = dot(P.m_direction, aabb.min());
	float pBL = dot(P.m_direction, aabb.max());

	float pBmin = fminf(fminf(pTR, pTL), fminf(pBR, pBL));
	float pBmax = fmaxf(fmaxf(pTR, pTL), fmaxf(pBR, pBL));

	float pBvel = dot(P.m_direction, bVel);
	float pPvel = dot(P.m_direction, pVel);

	float pPmax = dot(P.m_direction, P.m_position);

	CollisionDataSwept retVal;

	retVal.m_entryTime = (pBmin - pPmax) / (pPvel - pBvel);
	retVal.m_exitTime  = (pBmax - pPmax) / (pPvel - pBvel);
	retVal.m_collisionNormal = P.m_direction;

	return retVal;
}


CollisionData HullCollision(const Hull &Hull_0, const Hull &Hull_1)
{
	CollisionData bestColl;
	bestColl.m_penetrationDepth = INFINITY;

	Vec2 allNormalsArr[32];

	// Put all normals from both hulls into one array
	for (int ii = 0; ii < Hull_0.m_size; ++ii)
	{
		allNormalsArr[ii] = Hull_0.m_normals[ii];
	}	
	for (int ii = Hull_0.m_size, jj = 0; jj < Hull_1.m_size; ++ii, ++jj)
	{
		allNormalsArr[ii] = Hull_1.m_normals[jj];
	}

	// Go through each normal, to find the axis of collision
	for (int ii = 0; ii < Hull_0.m_size + Hull_1.m_size; ++ii)
	{
		float aMin = INFINITY, aMax = -INFINITY, 
			  bMin = INFINITY, bMax = -INFINITY; 

		for (int jj = 0; jj < Hull_0.m_size; ++jj)
		{
			float dotProduct_0 = dot(allNormalsArr[ii], Hull_0.m_vertArray[jj]);
			aMin > dotProduct_0 ? aMin = dotProduct_0 : aMin;
			aMax < dotProduct_0 ? aMax = dotProduct_0 : aMax;
		}
		for (int jj = 0; jj < Hull_1.m_size; ++jj)
		{
			float dotProduct_1 = dot(allNormalsArr[ii], Hull_1.m_vertArray[jj]);
			bMin > dotProduct_1 ? bMin = dotProduct_1 : bMin;
			bMax < dotProduct_1 ? bMax = dotProduct_1 : bMax;
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

CollisionDataSwept HullCollisionSwept(const Hull &Hull_0, const Vec2 Vel_0, const Hull &Hull_1, const Vec2 Vel_1)
{
	CollisionDataSwept bestColl;
	bestColl.m_entryTime = -INFINITY;
	bestColl.m_exitTime = INFINITY;

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
			aMin > dotProduct_0 ? aMin = dotProduct_0 : aMin;
			aMax < dotProduct_0 ? aMax = dotProduct_0 : aMax;
		}
		for (int jj = 0; jj < Hull_1.m_size; ++jj)
		{
			float dotProduct_1 = dot(allNormalsArr[ii], Hull_1.m_vertArray[jj]);
			bMin > dotProduct_1 ? bMin = dotProduct_1 : bMin;
			bMax < dotProduct_1 ? bMax = dotProduct_1 : bMax;
		}

		float pDr, pDl, pEntry, pExit, Dir;
		pDr = (aMin - bMax) / (dot(allNormalsArr[ii], (Vel_1 - Vel_0)));
		pDl = (bMin - aMax) / (dot(allNormalsArr[ii], (Vel_0 - Vel_1)));

		pEntry = fmaxf(pDr, pDl);
		pExit = fminf(pDr, pDl);

		Dir = copysignf(1, pDl - pDr);

		if (pEntry > bestColl.m_entryTime)
		{
			bestColl.m_entryTime = pEntry;
			bestColl.m_collisionNormal = allNormalsArr[ii] * Dir;
		}

		if (pExit < bestColl.m_exitTime)
		{
			bestColl.m_exitTime = pExit;
		}
	}

	//if (collisionY_swept.m_entryTime < collisionX_swept.m_entryTime || xSwept && !ySwept)
	//{
	//	retVal.m_collisionNormal = Vec2(1, 0) * collisionX_swept.m_collisionNormal;
	//	retVal.m_entryTime = collisionX_swept.m_entryTime;
	//	retVal.collides = ySwept || collisionY.resultIsCollision();
	//}
	//else if (ySwept) // collisionY_swept.m_entryTime >= collisionX_swept.m_entryTime
	//{
	//	retVal.m_collisionNormal = Vec2(1, 0) * collisionY_swept.m_collisionNormal;
	//	retVal.m_entryTime = collisionY_swept.m_entryTime;
	//	retVal.collides = xSwept || collisionX.resultIsCollision();
	//}
	//if (collisionY_swept.m_exitTime < collisionX_swept.m_exitTime || ySwept && !xSwept)
	//{
	//	retVal.m_exitTime = collisionY_swept.m_exitTime;
	//}
	//else if (xSwept) // collisionY_swept.m_exitTime >= collisionX_swept.m_exitTime
	//{
	//	retVal.m_exitTime = collisionX_swept.m_exitTime;
	//}

	return bestColl;
}

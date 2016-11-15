#include "Collider.h"

Collider::Collider(const Vec2 * verts, int size) : hull(verts, size)
{
	int xMin = INFINITY, xMax = -INFINITY, yMin = INFINITY, yMax = -INFINITY;
	Vec2 pos, he;
	for (int ii = 0; ii < size; ++ii)
	{
		xMin > verts[ii].x ? verts[ii].x : xMin;
		xMax < verts[ii].x ? verts[ii].x : xMax;
		yMin > verts[ii].y ? verts[ii].y : yMin;
		yMax < verts[ii].y ? verts[ii].y : yMax;
	}
	he = Vec2((xMax - xMin)*0.5, (yMax - yMin)*0.5);
	pos = Vec2(xMin + he.x, yMin + he.y);

	aabb = AABB(pos, he);
}

void Collider::debugDraw(const Mat3 &T, const Transform &Trans, unsigned color)
{
	Mat3 glob = T * Trans.getGlobalTransform();

	for (int ii = 0; ii < hull.m_size-1; ++ii)
	{
		Vec2 currPoint = hull.m_vertArray[ii];
		Vec2 nextPoint = hull.m_vertArray[ii+1];
		currPoint = (glob * Vec3(currPoint.x, currPoint.y, 1)).xy();
		nextPoint = (glob * Vec3(nextPoint.x, nextPoint.y, 1)).xy();

		sfw::drawLine(currPoint.x, currPoint.y, nextPoint.x, nextPoint.y, color);
	}

	Vec2 lastPoint = hull.m_vertArray[(hull.m_size - 1)];
	Vec2 origPoint = hull.m_vertArray[0];
	lastPoint = (glob * Vec3(lastPoint.x, lastPoint.y, 1)).xy();
	origPoint = (glob * Vec3(origPoint.x, origPoint.y, 1)).xy();

	sfw::drawLine(lastPoint.x, lastPoint.y, origPoint.x, origPoint.y, color);

	drawAABB(glob * aabb, color);
}

CollisionData ColliderCollision(const Transform &TA, const Collider &CA,
								const Transform &TB, const Collider &CB)
{
	// Check if the AABBs overlap
	CollisionData collData;
	collData = aabbCollision(TA.getGlobalTransform() * CA.aabb, TB.getGlobalTransform() * CB.aabb);

	// If the AABBs collide, check if the Hulls collide
	if (collData.m_penetrationDepth >= 0)
	{
		collData = HullCollision(TA.getGlobalTransform() * CA.hull, TB.getGlobalTransform() * CB.hull);
	}

	return collData;
}
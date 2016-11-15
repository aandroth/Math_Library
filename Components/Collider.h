#pragma once
#include "Shapes.h"
#include "Collision.h"
#include "ShapeDraw.h"
#include "Transform.h"

class Collider
{
public:
	AABB aabb;
	Hull hull;

	Collider(const Vec2 * verts, int size);
	void debugDraw(const Mat3 &T, const Transform &Trans, unsigned color);
};

CollisionData ColliderCollision(const Transform &TA, const Collider &CA,
								  const Transform &TB, const Collider &CB);
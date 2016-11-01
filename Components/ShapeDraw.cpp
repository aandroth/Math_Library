#include "ShapeDraw.h"

void drawCircle(const Circle &circle, unsigned color)
{
	sfw::drawCircle(circle.m_pos.x, circle.m_pos.y, circle.m_radius, 12, color);
}

void drawAABB(const AABB &aabb, unsigned color)
{
	sfw::drawLine(aabb.min().x, aabb.min().y, aabb.min().x, aabb.max().y, color); // bl -> tl
	sfw::drawLine(aabb.min().x, aabb.max().y, aabb.max().x, aabb.max().y, color); // tl -> tr
	sfw::drawLine(aabb.max().x, aabb.max().y, aabb.max().x, aabb.min().y, color); // tr -> br
	sfw::drawLine(aabb.max().x, aabb.min().y, aabb.min().x, aabb.min().y, color); // br -> bl
}

void drawBox(const Box &BOX, unsigned color)
{
	sfw::drawLine(BOX.pointsArr[0].x, BOX.pointsArr[0].y, BOX.pointsArr[1].x, BOX.pointsArr[1].y, color); // bl -> tl
	sfw::drawLine(BOX.pointsArr[1].x, BOX.pointsArr[1].y, BOX.pointsArr[2].x, BOX.pointsArr[2].y, color); // tl -> tr
	sfw::drawLine(BOX.pointsArr[2].x, BOX.pointsArr[2].y, BOX.pointsArr[3].x, BOX.pointsArr[3].y, color); // tr -> br
	sfw::drawLine(BOX.pointsArr[3].x, BOX.pointsArr[3].y, BOX.pointsArr[0].x, BOX.pointsArr[0].y, color); // br -> bl
}

void drawPlane(const Plane &plane, unsigned color)
{
	Vec2 point0 = (rotateByDegrees(angle(Vec2(plane.m_direction.x, plane.m_direction.y))) *  Vec3(plane.m_he.x, plane.m_he.y, 1)).xy();
	Vec2 point1 = (rotateByDegrees(angle(Vec2(plane.m_direction.x, plane.m_direction.y))) *  Vec3(plane.m_he.x, plane.m_he.y, 1)).xy();

	sfw::drawLine(plane.m_position.x - point0.x, plane.m_position.y - point0.y, plane.m_position.x + point1.x, plane.m_position.y + point1.y, color);
}

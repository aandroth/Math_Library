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


void drawPlane(const Plane &plane, unsigned color)
{
	sfw::drawLine(plane.pointsArr[0].x, plane.pointsArr[0].y, plane.pointsArr[1].x, plane.pointsArr[1].y, color); // bl -> tl
	sfw::drawLine(plane.pointsArr[1].x, plane.pointsArr[1].y, plane.pointsArr[2].x, plane.pointsArr[2].y, color); // tl -> tr
	sfw::drawLine(plane.pointsArr[2].x, plane.pointsArr[2].y, plane.pointsArr[3].x, plane.pointsArr[3].y, color); // tr -> br
	sfw::drawLine(plane.pointsArr[3].x, plane.pointsArr[3].y, plane.pointsArr[0].x, plane.pointsArr[0].y, color); // br -> bl
}

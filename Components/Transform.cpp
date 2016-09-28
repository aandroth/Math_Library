#include "Transform.h"

Vec2 Transform::getDirection()
{
	return fromAngle(facing);
}

void Transform::setDirection(const Vec2 &dir)
{
	facing = angle(dir);
}

void Transform::debugDraw()
{
	sfw::drawCircle(position.x, position.y, 12);

	Vec2 dirEnd = position + getDirection() * scale.x;
	Vec2 upEnd = position - perp(getDirection()) * scale.y;

	sfw::drawLine(position.x, position.y, dirEnd.x, dirEnd.y, RED);
	sfw::drawLine(position.x, position.y, upEnd.x, upEnd.y, GREEN);
}
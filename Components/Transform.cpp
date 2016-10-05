#include "Transform.h"

Transform::Transform() : position(Vec2(0, 0)), scale(Vec2(1, 1)), facing(0)
{
}

Vec2 Transform::getDirection() const
{
	return fromAngle(facing);
}

void Transform::setDirection(const Vec2 &dir)
{
	facing = angle(dir);
}

void Transform::debugDraw() const
{
	sfw::drawCircle(position.x, position.y, 12, 12, 0x888888FF);

	Vec2 dirEnd = position + getDirection() * scale.x * 20;
	Vec2 upEnd = position - perp(getDirection()) * scale.y * 20;

	sfw::drawLine(position.x, position.y, dirEnd.x, dirEnd.y, RED);
	sfw::drawLine(position.x, position.y, upEnd.x, upEnd.y, GREEN);
}
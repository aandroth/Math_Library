#include "Transform.h"

Transform::Transform(float x, float y, float w, float, float)
{
	m_parent = nullptr;
}

Vec2 Transform::getDirection() const
{
	return fromAngle(m_facing);
}

void Transform::setDirection(const Vec2 &dir)
{
	m_facing = angle(dir);
}

Vec2 Transform::getUp() const
{
	return perp(getDirection()) * -1;
}

Mat3 Transform::getLocalTransform() const
{
	Mat3 T = translate(m_position.x, m_position.y);
	Mat3 S = scale(m_scale.x, m_scale.y);
	Mat3 R = rotateByDegrees(m_facing);

	return T * R * S;
}

Mat3 Transform::getGlobalTransform() const
{
	if (m_parent == nullptr)
		return getLocalTransform();
	else
		return m_parent->getGlobalTransform() * getLocalTransform();
}

void Transform::debugDraw(const Mat3 &T) const
{
	Mat3 L = T * getGlobalTransform();

	Vec3 pos = Vec3(L.z1, L.z2, L.z3);

	Vec3 right = L * Vec3(100, 0, 1);
	Vec3 up =    L * Vec3(0, 10, 1);

	for (int ii = 0; ii < 3; ++ii)
	{
		std::cout << L.mm[ii][0] << " " << L.mm[ii][1] << " " << L.mm[ii][2] << "\n\n";
	}

	std::cout << pos.x << " " << pos.y << "\n";
	std::cout << right.x << " " << right.y << " " << right.z << "\n";

	sfw::drawLine(pos.x, pos.y, right.x, right.y, RED);
	sfw::drawLine(pos.x, pos.y, up.x, up.y, GREEN);

	sfw::drawCircle(pos.x, pos.y, 12, 12, WHITE);
	//sfw::drawCircle(m_position.x, m_position.y, 12, 12, 0x888888FF);
}
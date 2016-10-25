#include "Transform.h"

#include <iostream>
using std::cout;

Transform::Transform(float x, float y, float w, float h, float a)
{
	m_position = Vec2(x, y);
	m_scale = Vec2(w, h);
	m_facing = a;

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

void Transform::rotateLocalTransform(float const &R)
{
	m_facing += R;
}

void Transform::translateLocalTransform(float const &T)
{
	moveBy = T;
}

Mat3 Transform::getLocalTransform() const
{
	Mat3 T = translate(m_position.x, m_position.y) * translateByMat3;
	Mat3 S = scale(m_scale.x, m_scale.y);
	Mat3 R = rotateByDegrees(m_facing);

	return  T * R * S;
}

Mat3 Transform::getSunTransform() const
{
	Mat3 T = translate(m_parent->m_position.x, m_parent->m_position.y);
	Mat3 S = scale(m_parent->m_scale.x, m_parent->m_scale.y);
	Mat3 R = rotateByDegrees(m_parent->m_facing * 100001 * (1/determinant(Mat2(m_position, m_parent->m_position))));

	//cout << "m_position.x: " << (1 / determinant(Mat2(m_position, m_parent->m_position))) << "\n";
	//cout << "m_position.y: " << R.z2 << "\n";

	return T * R * S;
}

Mat3 Transform::getGlobalTransform() const
{
	if (m_parent == nullptr)
		return getLocalTransform();
	else
		//return getSunTransform() * getLocalTransform();
		return m_parent->getGlobalTransform() * getLocalTransform();
}

Vec2 Transform::getGlobalPosition() const
{
	Mat3 L = getGlobalTransform();

	return Vec2(L.z1, L.z2);
}

void Transform::debugDraw(const Mat3 &T)
{
	Mat3 L = T * getGlobalTransform();

	Vec3 pos = Vec3(L.z1, L.z2, L.z3);
	//Vec3 right = L * Vec3(20, 0, 1);

	//if(m_parent == nullptr)
	//sfw::drawLine(pos.x, pos.y, right.x, right.y, GREEN);

	sfw::drawCircle(pos.x, pos.y, 12, 12, GREEN);
	//cout << "pos.x: " << getGlobalTransform().z1 << "\n";
	//cout << "pos.y: " << getGlobalTransform().z2 << "\n";
}
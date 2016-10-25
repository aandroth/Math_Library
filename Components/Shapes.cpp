#include "Shapes.h"

Circle::Circle(Circle &circle)
{
	m_radius = circle.m_radius;
	m_pos = circle.m_pos;
}

Circle::Circle(Vec2 new_pos, float new_radius)
{
	m_radius = new_radius;
	m_pos = new_pos;
}

Circle operator* (const Mat3 &MAT3, const Circle &rhs)
{
	Vec3 vec3_scale = MAT3 * Vec3(rhs.m_radius, rhs.m_radius, 1);
	Vec3 vec3_pos   = MAT3 * Vec3(rhs.m_pos.x, rhs.m_pos.y, 1);
	Circle return_circle(Vec2(vec3_pos.x, vec3_pos.y), rhs.m_radius);

	if (vec3_scale.x > vec3_scale.y)
	{
		return_circle.m_radius = vec3_scale.x;
	}
	else
	{
		return_circle.m_radius = vec3_scale.y;
	}

	return return_circle;
}

bool operator== (const Circle &lhs, const Circle &rhs)
{
	return ((floatsAlmostEqual(lhs.m_radius, rhs.m_radius)) && (lhs.m_pos == rhs.m_pos));
}

AABB::AABB(float pos_x, float pos_y, float he_x, float he_y)
{
	m_pos = Vec2(pos_x, pos_y);
	m_he = Vec2(he_x, he_y);
}

AABB::AABB(Vec2 new_pos, Vec2 new_he)
{
	m_pos = new_pos;
	m_he = new_he;
}

Vec2 AABB::min() const
{
	return m_pos - m_he;
}

Vec2 AABB::max() const
{
	return m_pos + m_he;
}

AABB operator*(const Mat3 &MAT3, const AABB &aabb)
{
	Vec3 vec3_trans = MAT3 * Vec3(aabb.m_he.x, aabb.m_he.y, 1);

	return AABB(aabb.m_pos.x, aabb.m_pos.y, vec3_trans.x, vec3_trans.y);
}

//Plane::Plane(float pos_x0, float pos_y0, float pos_x1, float pos_y1)
//{
//	m_pos0 = Vec2(pos_x0, pos_y0);
//	m_pos1 = Vec2(pos_x1, pos_y1);
//}

//Plane::Plane(Vec2 pos0, Vec2 pos1)
//{
//	m_pos0 = pos0;
//	m_pos1 = pos1;
//}
//
//Plane operator*(const Mat3 &MAT3, const Plane &PLANE)
//{
//	Vec3 vec3_trans0 = MAT3 * Vec3(PLANE.m_pos0.x, PLANE.m_pos0.y, 1);
//	Vec3 vec3_trans1 = MAT3 * Vec3(PLANE.m_pos1.x, PLANE.m_pos1.y, 1);
//
//	return Plane(vec3_trans0.x, vec3_trans0.y, vec3_trans1.x, vec3_trans1.y);
//}


Ray::Ray(float pos_x0, float pos_y0, float pos_x1, float pos_y1)
{
	m_pos0 = Vec2(pos_x0, pos_y0);
	m_pos1 = Vec2(pos_x1, pos_y1);
}
Ray::Ray(Vec2 pos0, Vec2 pos1)
{
	m_pos0 = pos0;
	m_pos1 = pos1;
}

Ray operator*(const Mat3 &MAT3, const Ray &RAY)
{
	Vec3 vec3_trans0 = MAT3 * Vec3(RAY.m_pos0.x, RAY.m_pos0.y, 1);
	Vec3 vec3_trans1 = MAT3 * Vec3(RAY.m_pos1.x, RAY.m_pos1.y, 1);

	return Ray(vec3_trans0.x, vec3_trans0.y, vec3_trans1.x, vec3_trans1.y);
}

Hull::Hull()
{

}
//
//Hull operator*(const Mat3 &MAT3, const Hull &HULL)
//{
//
//}
#pragma once

#include "Mat3.h"
#include "Vec2.h"

struct Circle 
{
	Circle(Vec2 new_pos, float new_radius);
	Circle(Circle &circle);

	Vec2 m_pos;
	float m_radius;
};

Circle operator*(const Mat3 &MAT3, const Circle &CIR);
bool operator==(const Circle & lhs, const Circle &rhs);

struct AABB
{
	Vec2 m_pos, m_he;

	AABB(float pos_x, float pos_y, float dim_x, float dim_y);
	AABB(Vec2 new_pos, Vec2 new_dim);

	Vec2 min() const;
	Vec2 max() const;
};
AABB operator*(const Mat3 &MAT3, const AABB &aabb);

//struct Plane
//{
//	Plane(float pos_x0, float pos_y0, float x1, float y1);
//	Plane(Vec2 pos0, Vec2 pos1);
//
//	Vec2 m_pos0, m_pos1;
//};
//
//Plane operator*(const Mat3 &MAT3, const Plane &PLANE);

struct Ray
{
public:
	Ray(float pos_x0, float pos_y0, float x1, float y1);
	Ray(Vec2 pos0, Vec2 pos1);

	Vec2 m_pos0, m_pos1;
};

Ray operator*(const Mat3 &MAT3, const Ray &RAY);

struct Hull
{
	Hull();
};
Hull operator*(const Mat3 &MAT3, const Hull &HULL);

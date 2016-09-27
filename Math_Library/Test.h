#pragma once

#include <cmath>
struct Vec2
{
	float x, y;
	Vec2(float, float);

};

bool operator== (const Vec2 &lhs, const Vec2 &rhs);
bool operator!= (const Vec2 &lhs, const Vec2 &rhs);

Vec2 operator+ (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator+= (Vec2 &lhs, const Vec2 &rhs);

Vec2 operator- (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator-= (Vec2 &lhs, const Vec2 &rhs);

Vec2 operator* (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator*= (Vec2 &lhs, const Vec2 &rhs);

Vec2 operator/ (const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator/= (Vec2 &lhs, const Vec2 &rhs);

Vec2 operator* (const Vec2 &lhs, const float &rhs);
Vec2 operator*= (Vec2 &lhs, const float &rhs);

Vec2 operator/ (const Vec2 &lhs, const float &rhs);
Vec2 operator/= (Vec2 &lhs, const float &rhs);

float magnitude(const Vec2 &v);

struct Vec3
{
	float x, y;
	Vec3(float, float, float);

};

bool operator== (const Vec3 &lhs, const Vec3 &rhs);
bool operator!= (const Vec3 &lhs, const Vec3 &rhs);

Vec3 operator+ (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator+= (Vec3 &lhs, const Vec3 &rhs);

Vec3 operator- (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator-= (Vec3 &lhs, const Vec3 &rhs);

Vec3 operator* (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator*= (Vec3 &lhs, const Vec3 &rhs);

Vec3 operator/ (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator/= (Vec3 &lhs, const Vec3 &rhs);

Vec3 operator* (const Vec3 &lhs, const float &rhs);
Vec3 operator*= (Vec3 &lhs, const float &rhs);

Vec3 operator/ (const Vec3 &lhs, const float &rhs);
Vec3 operator/= (Vec3 &lhs, const float &rhs);

float magnitude(const Vec3 &v);



struct Vec3
{
	float x, y, z;
	Vec3(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}
};

struct Plane
{
	float a, b, c, d;
	Plane(float newA, float newB, float newC, float newD)
	{
		a = newA;
		b = newB;
		c = newC;
		d = newD;
	}
};

int doNothing(int);
int orderTwo_Formula(int);
Vec2 quadratic(int, int, int);
float linear_blend(int, int, int);
float vector_difference(Vec2, Vec2);
float inner_product(Vec3, Vec3);
float point_plane_distance(Vec3, Plane);
float bezier_curve(float, Plane);
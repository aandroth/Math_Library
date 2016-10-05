#pragma once

#include "Flops.h"
#include <cmath>

#ifndef TEST_H
#define TEST_H

struct Vec2
{
	float x, y;
	Vec2();
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

// Reduce vector's length to 1
// v/magnitude(v)
Vec2 normal(const Vec2 &v);

// Scalar Projection : width of the right angle between two vectors
// x1*x2 + y1*y2
float dot(const Vec2 &lhs, const Vec2 &rhs);

// Find the angle between two vectors
// acos(dot(normal(v1), normal(v2)))
float angleBetween(const Vec2 &lhs, const Vec2 &rhs);

// Find a right angle perpendicular vector (2D only!)
// (y,-x)
Vec2 perp(const Vec2 &v);

// Find the angle of the vector (2D only!)
// atan2f(y,x)
float angle(const Vec2 &v);

// vec2{cos(a), sin(a)};
Vec2 fromAngle(float a);

Vec2 lerp(const Vec2 start, const Vec2 end, const float alpha);

Vec2 quadBezier(const Vec2 start, const Vec2 mid, const Vec2 end, const float alpha);

Vec2 cubicBezier(const Vec2 start, const Vec2 mid1, const Vec2 mid2, const Vec2 end, const float alpha);

Vec2 hermiteSpline(const Vec2 start, const Vec2 end, const Vec2 tangent0, const Vec2 tangent1, float alpha);

Vec2 cardinalSpline(const Vec2 start, const Vec2 mid, const Vec2 end, float tightness, float alpha);

struct Vec3
{
	float x, y, z;
	Vec3();
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

// Scalar Projection : width of the right angle between two vectors
float dot(const Vec3 &lhs, const Vec3 &rhs);

Vec3 normal(const Vec3 &v);

// Find the angle between two vectors
float angleBetween(const Vec3 &lhs, const Vec3 &rhs);

// Find a vector perpendicular to the plane created by two vectors
Vec3 cross(const Vec3 &lhs, const Vec3 &rhs);

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

#endif
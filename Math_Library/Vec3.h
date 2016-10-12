#pragma once

#include "Flops.h"
#include <cmath>

#ifndef VEC3_H
#define VEC3_H

union Vec3
{
	float v[3];
	struct
	{
		float x, y, z;
	};
	Vec3();
	Vec3(float, float, float);

	float operator[](unsigned idx) const;
	float &operator[](unsigned idx);
};

bool operator== (const Vec3 &lhs, const Vec3 &rhs);
bool operator!= (const Vec3 &lhs, const Vec3 &rhs);

Vec3 operator+ (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator+= (Vec3 &lhs, const Vec3 &rhs);

Vec3 operator- (const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator-= (Vec3 &lhs, const Vec3 &rhs);

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

#endif
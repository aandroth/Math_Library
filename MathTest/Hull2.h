#pragma once
#include "Vec2.h"
#include "Mat3.h"

struct Hull
{
	Vec2 m_vertArray[16];
	Vec2 m_normals[16];
	unsigned int m_size;

	void updateNormals();
	Hull();
	Hull(const Vec2 *a_verts, unsigned a_size);
};
bool operator==(const Hull &lhs, const Hull &rhs);

Hull operator*(const Mat3 &MAT3, const Hull &HULL);

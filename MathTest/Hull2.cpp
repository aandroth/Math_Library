#include "Hull2.h"


Hull::Hull()
{

}

Hull::Hull(const Vec2 *a_verts, unsigned a_size)
{
	for (int ii = 0; ii < a_size; ++ii)
	{
		m_vertArray[ii] = a_verts[ii];
	}
	m_size = a_size;
}

void Hull::updateNormals()
{
	for (int ii = 0; ii < m_size - 1; ++ii)
	{
		m_normals[ii] = perp(normal(m_vertArray[ii + 1] - m_vertArray[ii]));
	}

	m_normals[m_size] = perp(normal(m_vertArray[0] - m_vertArray[m_size]));
}

bool operator==(const Hull &lhs, const Hull &rhs)
{
	if (lhs.m_size != rhs.m_size)
	{
		return false;
	}

	for (int ii = 0; ii < lhs.m_size; ++ii)
	{
		if (lhs.m_vertArray[ii] != rhs.m_vertArray[ii])
		{
			return false;
		}
	}

	return true;
}

Hull operator*(const Mat3 &MAT3, const Hull &HULL)
{
	Hull retHull;
	retHull.m_size = HULL.m_size;

	for (int ii = 0; ii < HULL.m_size; ++ii)
	{
		retHull.m_vertArray[ii] = (MAT3 * Vec3(HULL.m_vertArray[ii].x, HULL.m_vertArray[ii].y, 1)).xy();

		retHull.m_normals[ii] = (MAT3 * Vec3(HULL.m_normals[ii].x, HULL.m_normals[ii].y, 0)).xy();
	}

	return retHull;
}
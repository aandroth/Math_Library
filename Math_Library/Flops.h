
#ifndef FLOPS_H
#define FLOPS_H

#pragma once
#include <cmath>


const float PI = 3.14159265359;

static bool floatsAlmostEqual(float f0, float f1)
{
	if (abs(f1 - f0) < 0.00000007)
	{
		return true;
	}

	return false;
}

static float degreesToRadians(float deg)
{
	return (deg * PI) / 180.0;
}

static float radiansToDegrees(float rad)
{
	return (rad * 180.0) / PI;
}

#endif
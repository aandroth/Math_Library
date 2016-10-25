#pragma once
#include "Mat3.h"
#include "Transform.h"
#include "sfwdraw.h"

class SpaceshipRenderer
{
public:
	float m_width, m_height;
	unsigned m_color;

	SpaceshipRenderer(float new_width = 10, float new_height = 20, unsigned new_color = GREEN);

	void render(const Mat3 &T, const Transform & trans) const;
};
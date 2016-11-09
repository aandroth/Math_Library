#include "SpaceShipRenderer.h"

SpaceshipRenderer::SpaceshipRenderer(float new_width, float new_height, unsigned new_color)
{
	m_width = new_width;
	m_height = new_height;
	m_color = new_color;
}

void SpaceshipRenderer::render(const Mat3 &T, const Transform & trans) const
{
	Mat3 shipTrans = T * trans.getGlobalTransform();

	// Draw rotated by -90 degrees:
	Vec3 frontEnd =  shipTrans * Vec3(m_height,      0,       1),
		 backEnd =   shipTrans * Vec3(-m_height*0.5, 0,       1),
		 rightWing = shipTrans * Vec3(0,             m_width, 1),
		 leftWing =  shipTrans * Vec3(0,            -m_width, 1);

	sfw::drawLine(frontEnd.x,  frontEnd.y,  leftWing.x,  leftWing.y,  m_color);
	sfw::drawLine(leftWing.x,  leftWing.y,  backEnd.x,   backEnd.y,   m_color);
	sfw::drawLine(backEnd.x,   backEnd.y,   rightWing.x, rightWing.y, m_color);
	sfw::drawLine(rightWing.x, rightWing.y, frontEnd.x,  frontEnd.y,  m_color);
}
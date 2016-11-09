#include "PlanetRenderer.h"

PlanetRenderer::PlanetRenderer(unsigned new_color, float new_radius)
{
	m_color = new_color;
	m_radius = new_radius;
}

void PlanetRenderer::draw(Mat3 &camMat3, Transform &planetTransform)
{
	Mat3 planetTrans = camMat3 * planetTransform.getGlobalTransform();

	sfw::drawCircle(planetTrans.z1, planetTrans.z2, m_radius, 12, m_color);
}

float PlanetRenderer::getRadius()
{
	return m_radius;
}
void PlanetRenderer::setRadius(float new_radius)
{
	m_radius = new_radius;
}
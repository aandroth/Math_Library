#include "PlanetRenderer.h"

PlanetRenderer::PlanetRenderer(unsigned new_color, float new_radius)
{
	m_color = new_color;
	m_radius = new_radius;
}

void PlanetRenderer::draw(Transform &planetTransform) const
{
	sfw::drawCircle(planetTransform.getGlobalPosition().x, planetTransform.getGlobalPosition().y, m_radius, 12, m_color);
}
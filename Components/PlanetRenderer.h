#include "Transform.h"

class PlanetRenderer
{
public:
	unsigned m_color;
	float m_radius;

	PlanetRenderer(unsigned, float);

	void PlanetRenderer::draw(Mat3 &camMat3, Transform &planetTransform);
	float getRadius();
	void setRadius(float radius);
};
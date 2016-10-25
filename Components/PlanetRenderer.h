#include "Transform.h"

class PlanetRenderer
{
public:
	unsigned m_color;
	float m_radius;

	PlanetRenderer(unsigned, float);

	void draw(Transform &planetTransform) const;
};
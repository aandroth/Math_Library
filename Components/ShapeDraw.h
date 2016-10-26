#pragma once

#include "Shapes.h"
#include "sfwdraw.h"

void drawCircle(const Circle &C, unsigned color = YELLOW);

void drawAABB(const AABB &aabb, unsigned color = YELLOW);

void drawPlane(const Plane &plane, unsigned color = RED);
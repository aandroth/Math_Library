#pragma once

#include "Transform.h"

class Camera
{
public:

	Camera();

	Transform cameraTransform;
	Vec2 screenCenter, screenZoom;

	float cameraLerpSnap;

	void calculateCameraTransform(Transform playerTransform, float deltaTime);

	Mat3 getCameraTransform();
};


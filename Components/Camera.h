#pragma once

#include "Transform.h"

class Camera
{
public:

	Camera(Transform cameraTransform, Vec2 screenCenter, Vec2 screenZoom, float cameraLerpSnap);

	Transform m_cameraTransform;
	Vec2 m_screenCenter, m_screenZoom;
	float m_cameraLerpSnap;

	void calculateCameraTransform(Transform playerTransform, float deltaTime);

	Mat3 getCameraTransform();
};


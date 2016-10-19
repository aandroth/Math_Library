#include "Camera.h"

Camera::Camera(Transform cameraTransform, Vec2 screenCenter, Vec2 screenZoom, float cameraLerpSnap)
{
	m_cameraTransform = cameraTransform;
	m_screenCenter = screenCenter;
	m_screenZoom = screenZoom;
	m_cameraLerpSnap = cameraLerpSnap;
}

void Camera::calculateCameraTransform(Transform playerTransform, float deltaTime)
{
	m_cameraTransform.m_position = lerp(m_cameraTransform.m_position,
		playerTransform.getGlobalPosition(),
		sfw::getDeltaTime() * m_cameraLerpSnap);
}

Mat3 Camera::getCameraTransform()
{
	Mat3 proj = translate(m_screenCenter.x, m_screenCenter.y) * scale(m_screenZoom.x, m_screenZoom.y);
	Mat3 view = inverse(m_cameraTransform.getGlobalTransform());
	return proj * view;
}
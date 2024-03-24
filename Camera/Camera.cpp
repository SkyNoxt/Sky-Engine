
#include <cmath>
#include <numbers>

#include "Camera.h"

const float Camera::DEG_TO_RAD = std::numbers::pi / 180;
// const float Camera::RAD_TO_DEG = 180 / std::numbers::pi;

Camera::Camera(float fLength, float fov, float targetRatio, float zNear, float zFar)
	: cameraMatrix(Matrix4<>())
	, viewMatrix(Matrix4<>())
	//, focalLength(fLength)
	, fieldOfView(fov)
	, aspectRatio(targetRatio)
	, nearPlane(zNear)
	, farPlane(zFar)
	, scale(std::tan(fieldOfView * 0.5 * DEG_TO_RAD))
{

	float invScale = 1.0 / scale;
	float distance = farPlane - nearPlane;

	projectionMatrix = {
		invScale / aspectRatio, 0, 0, 0,
		0, invScale, 0, 0,
		0, 0, -farPlane / distance, -1,
		0, 0, -farPlane * (nearPlane / distance), 0
	};

	// aperture = tan(fieldOfView / 2 * DEG_TO_RAD) * focalLength * 2;
	// fieldOfView = atan((aperture / 2) / focalLength) * 2 * RAD_TO_DEG;
}

Ray Camera::castRay(unsigned int width, unsigned int height, unsigned int x, unsigned int y) const
{
	float dirX = (2 * (x + 0.5) / (float)width - 1) * aspectRatio * scale;
	float dirY = (1 - 2 * (y + 0.5) / (float)height) * scale;

	Vector3<> dir = (cameraMatrix * Vector3<>{ dirX, dirY, -1.0 }).normalize();

	return Ray({ cameraMatrix.wx, cameraMatrix.wy, cameraMatrix.wz }, dir);
}

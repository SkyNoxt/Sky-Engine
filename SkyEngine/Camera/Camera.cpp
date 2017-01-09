
#include "Camera.h"

Camera::Camera(float fLength, float fov, float targetRatio, float zNear, float zFar)
{
	focalLength = fLength;
	fieldOfView = fov;
	aspectRatio = targetRatio;

	nearPlane = zNear;
	farPlane = zFar;

	scale = tan(fieldOfView * 0.5 * DEG_TO_RAD);

	cameraMatrix = Matrix4<float>();
	viewMatrix = Matrix4<float>();
	projectionMatrix = Matrix4<float>();

	float invScale = 1.0 / scale;
	float distance = farPlane - nearPlane;

	projectionMatrix.xx = invScale / aspectRatio;
	projectionMatrix.yy = invScale;
	projectionMatrix.zz = -farPlane / distance;
	projectionMatrix.wz = -farPlane * (nearPlane / distance);
	projectionMatrix.zw = -1;
	projectionMatrix.ww = 0;

	//aperture = tan(fieldOfView / 2 * DEG_TO_RAD) * focalLength * 2;
	//fieldOfView = atan((aperture / 2) / focalLength) * 2 * RAD_TO_DEG;
}

Ray Camera::castRay(unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
	float dirX = (2 * (x + 0.5) / (float)width - 1) * aspectRatio * scale;
	float dirY = (1 - 2 * (y + 0.5) / (float)height) * scale;

	Vector3<float> dir = (Vector3<float>(dirX, dirY, -1.0) * cameraMatrix).normalize();

	return Ray(Vector3<float>(cameraMatrix.wx, cameraMatrix.wy, cameraMatrix.wz), dir);
}

Camera::~Camera()
{
}

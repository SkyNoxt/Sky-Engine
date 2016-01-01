
#include "Camera.h"

Camera::Camera(float fLength, float fov, float targetRatio)
{
	focalLength = fLength;
	fieldOfView = fov;
	aspectRatio = targetRatio;
	scale = tan(fieldOfView * 0.5 * DEG_TO_RAD);

	viewMatrix = Matrix4<float>();

	//aperture = tan(fieldOfView / 2 * DEG_TO_RAD) * focalLength * 2;
	//fieldOfView = atan((aperture / 2) / focalLength) * 2 * RAD_TO_DEG;
}

Ray Camera::castRay(unsigned int width, unsigned int height, unsigned int x, unsigned int y)
{
    float dirX = (2 * (x + 0.5) / (float)width - 1) * aspectRatio * scale;
    float dirY = (1 - 2 * (y + 0.5) / (float)height) * scale;

    Vector3<float> dir = Vector3<float>(dirX, dirY, -1.0) * viewMatrix;

    dir = dir.normalize();

    return Ray(Vector3<float> { viewMatrix.wx, viewMatrix.wy, viewMatrix.wz }, dir);
}

Camera::~Camera()
{
	
}

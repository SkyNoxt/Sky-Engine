
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

Camera::~Camera()
{
	
}

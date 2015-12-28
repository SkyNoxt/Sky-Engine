
#pragma once

#include <math.h>

#include <Math/Matrix4.h>

#define DEG_TO_RAD M_PI / 180
//#define RAD_TO_DEG 180 / M_PI

class Camera
{

public:

	//Constructors
	Camera(float fLength, float fov, float targetRatio);

	//Member functions

	//destructor
	~Camera();

private:

	float focalLength;
	float fieldOfView;
	float aspectRatio;
	float scale;

	Matrix4<float> viewMatrix;

};

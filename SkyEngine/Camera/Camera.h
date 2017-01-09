﻿
#pragma once

#include <math.h>

#include <Math/Matrix4.h>

#include <Ray.h>

#define DEG_TO_RAD M_PI / 180
//#define RAD_TO_DEG 180 / M_PI

class Camera
{

public:
	//Constructors
	Camera(float fLength, float fov, float targetRatio, float zNear = 0, float zFar = Ray::maxLength);

	//Member functions
	Ray castRay(unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	//destructor
	~Camera();

	//private:

	float focalLength;
	float fieldOfView;
	float aspectRatio;

	float nearPlane;
	float farPlane;

	float scale;

	Matrix4<float> cameraMatrix;
	Matrix4<float> viewMatrix;
	Matrix4<float> projectionMatrix;
};

﻿
#pragma once

#include <Math/Matrix4.h>

#include <Ray.h>

using Sky::Math::Matrix4;

class Camera
{

  public:
	static const float DEG_TO_RAD;
	// static const float RAD_TO_DEG;

	Matrix4<> cameraMatrix;
	Matrix4<> viewMatrix;
	Matrix4<> projectionMatrix;

	// Constructors
	Camera(float fLength, float fov, float targetRatio, float zNear = 0, float zFar = Ray::MAX_LENGTH);

	// Member functions
	Ray castRay(unsigned int width, unsigned int height, unsigned int x, unsigned int y) const;

	// destructor
	~Camera() = default;

  private:
	// float focalLength;
	float fieldOfView;
	float aspectRatio;

	float nearPlane;
	float farPlane;

	float scale;
};

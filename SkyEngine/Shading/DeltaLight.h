
#pragma once

#include <Math/Matrix4.h>
#include <Math/Vector3.h>

class DeltaLight
{

public:
	Matrix4<float> lightMatrix;
	Vector3<float> color;
	float intensity;

	//Constructor
	DeltaLight(const Vector3<float>& clr, float ntnst);

	//Member functions

	//Destructor
	~DeltaLight();
};

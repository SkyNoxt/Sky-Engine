
#pragma once

#include <Math/Matrix4.h>
#include <Math/Vector3.h>

class DeltaLight
{

public:
	Matrix4<> lightMatrix;
	Vector3<> color;
	float intensity;

	//Constructor
	DeltaLight(const Vector3<>& clr, float ntnst);

	//Member functions

	//Destructor
	~DeltaLight();
};

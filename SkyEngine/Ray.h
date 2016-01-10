
#pragma once

#include <limits>

#include <Math/Vector3.h>

class Ray
{

public:

	static const float maxLength;

	Vector3<float> origin;
	Vector3<float> direction;

	//Constructor
	Ray(const Vector3<float>& org, const Vector3<float>& dir);

	//Destructor
	~Ray();
		
};

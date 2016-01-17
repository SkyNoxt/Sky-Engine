
#pragma once

#include <limits>

#include <Math/Vector3.h>

class Ray
{

public:

	static const float maxLength;

	//Member variables
	Vector3<float> origin;
	Vector3<float> direction;

	Vector3<float> inverseDirection;
	int sign[3];

	//Constructor
	Ray(const Vector3<float>& org, const Vector3<float>& dir);

	//Destructor
	~Ray();
		
};

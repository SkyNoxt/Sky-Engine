
#pragma once

#include <limits>

#include <Math/Vector3.h>

class Ray
{

public:
	static const float MAX_LENGTH;

	//Member variables
	Vector3<> origin;
	Vector3<> direction;

	Vector3<> inverseDirection;
	int sign[3];

	//Constructor
	Ray(const Vector3<>& org, const Vector3<>& dir);

	//Destructor
	~Ray();
};

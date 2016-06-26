
#pragma once

#include <Math/Vector3.h>

#include <Ray.h>

class Box
{

public:

	Vector3<float> bounds[2];

	//Constructor
	Box(const Vector3<float>& min, const Vector3<float>& max);
	Box();

	//Member function
	bool intersect(const Ray& ray, float& distance);

	//Destructor
	~Box();
		
};

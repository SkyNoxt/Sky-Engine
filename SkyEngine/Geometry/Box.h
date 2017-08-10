
#pragma once

#include <Math/Vector3.h>

#include <Ray.h>

template <class T = float>
class Box
{

public:
	Vector3<T> bounds[2];

	//Constructor
	Box(const Vector3<T>& min, const Vector3<T>& max);
	Box();

	//Member function
	bool intersect(const Ray& ray, T& distance);

	//Destructor
	~Box();
};

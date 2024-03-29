﻿
#pragma once

#include <Ray.h>

namespace Sky::Geometry
{
	template <typename T = float>
	class Box
	{
	  public:
		Vector3<T> bounds[2];

		// Constructor
		Box(const Vector3<T>& min, const Vector3<T>& max);

		// Member function
		bool intersect(const Ray& ray, T& distance) const;

		// Destructor
		~Box() = default;
	};
}

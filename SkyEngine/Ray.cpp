﻿
#include <limits>

#include "Ray.h"

const float Ray::MAX_LENGTH = std::numeric_limits<float>::max();

Ray::Ray(const Vector3<>& org, const Vector3<>& dir)
	: origin(org)
	, direction(dir)
	, inverseDirection({ 1 / direction.x, 1 / direction.y, 1 / direction.z })
	, sign{ (inverseDirection.x < 0), (inverseDirection.y < 0), (inverseDirection.z < 0) }
{
}


#include "Ray.h"

const float Ray::MAX_LENGTH = std::numeric_limits<float>::max();

Ray::Ray(const Vector3<>& org, const Vector3<>& dir)
	: origin(org)
	, direction(dir)
	, inverseDirection(Vector3<>{ 1 / direction.x, 1 / direction.y, 1 / direction.z })
{
	sign[0] = (inverseDirection.x < 0);
	sign[1] = (inverseDirection.y < 0);
	sign[2] = (inverseDirection.z < 0);
}

Ray::~Ray()
{
}

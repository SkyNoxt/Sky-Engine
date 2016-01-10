
#include "Ray.h"

const float Ray::maxLength = std::numeric_limits<float>::max();

Ray::Ray(const Vector3<float>& org, const Vector3<float>& dir)
{
	origin = org;
	direction = dir;
}

Ray::~Ray()
{
	
}

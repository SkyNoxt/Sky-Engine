
#include "Ray.h"

Ray::Ray(const Vector3<float>& org, const Vector3<float>& dir)
{
	origin = org;
	direction = dir;
}

Ray::~Ray()
{
	
}

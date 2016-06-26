
#include "Box.h"

Box::Box(const Vector3<float>& min, const Vector3<float>& max)
{
	bounds[0] = min;
	bounds[1] = max;
}

Box::Box()
{
	bounds[0] = 0.0;
	bounds[1] = 0.0;
}

bool Box::intersect(const Ray& ray, float& distance)
{
	float xMin, xMax, yMin, yMax, zMin, zMax;

	xMin = (bounds[ray.sign[0]].x - ray.origin.x) * ray.inverseDirection.x;
	xMax = (bounds[1 - ray.sign[0]].x - ray.origin.x) * ray.inverseDirection.x;

	yMin = (bounds[ray.sign[1]].y - ray.origin.y) * ray.inverseDirection.y;
	yMax = (bounds[1 - ray.sign[1]].y - ray.origin.y) * ray.inverseDirection.y;

	if ((xMin > yMax) || (yMin > xMax))
		return false;

	if (yMin > xMin)
		xMin = yMin;
	if (yMax < xMax)
		xMax = yMax;

	zMin = (bounds[ray.sign[2]].z - ray.origin.z) * ray.inverseDirection.z;
	zMax = (bounds[1 - ray.sign[2]].z - ray.origin.z) * ray.inverseDirection.z;

	if ((xMin > zMax) || (zMin > xMax))
		return false;

	if (zMin > xMin)
		xMin = zMin;
	if (zMax < xMax)
		xMax = zMax;

	distance = xMin;

	if(distance < 0)
	{
		distance = xMax;
		if(distance < 0 ) return false;
	}

	return true;
}

Box::~Box()
{
	
}

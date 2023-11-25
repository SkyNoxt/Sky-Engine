
#include "Box.h"

using Sky::Geometry::Box;

template <typename T>
Box<T>::Box(const Vector3<T>& min, const Vector3<T>& max)
	: bounds{ min, max }
{
}

template <typename T>
bool Box<T>::intersect(const Ray& ray, T& distance) const
{
	T xMin = (bounds[ray.sign[0]].x - ray.origin.x) * ray.inverseDirection.x;
	T xMax = (bounds[1 - ray.sign[0]].x - ray.origin.x) * ray.inverseDirection.x;

	T yMin = (bounds[ray.sign[1]].y - ray.origin.y) * ray.inverseDirection.y;
	T yMax = (bounds[1 - ray.sign[1]].y - ray.origin.y) * ray.inverseDirection.y;

	if((xMin > yMax) || (yMin > xMax))
		return false;

	if(yMin > xMin)
		xMin = yMin;
	if(yMax < xMax)
		xMax = yMax;

	T zMin = (bounds[ray.sign[2]].z - ray.origin.z) * ray.inverseDirection.z;
	T zMax = (bounds[1 - ray.sign[2]].z - ray.origin.z) * ray.inverseDirection.z;

	if((xMin > zMax) || (zMin > xMax))
		return false;

	if(zMin > xMin)
		xMin = zMin;
	if(zMax < xMax)
		xMax = zMax;

	distance = xMin >= 0 ? xMin : xMax;
	return !(distance < 0);
}

template class Sky::Geometry::Box<>;

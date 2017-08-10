
#include "DeltaLight.h"

DeltaLight::DeltaLight(const Vector3<>& clr, float ntnst)
	: lightMatrix(Matrix4<>())
	, color(clr)
	, intensity(ntnst)
{
}

DeltaLight::~DeltaLight()
{
}

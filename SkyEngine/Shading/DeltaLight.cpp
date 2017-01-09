
#include "DeltaLight.h"

DeltaLight::DeltaLight(const Vector3<float>& clr, float ntnst)
{
	lightMatrix = Matrix4<float>();
	color = clr;
	intensity = ntnst;
}

DeltaLight::~DeltaLight()
{
}

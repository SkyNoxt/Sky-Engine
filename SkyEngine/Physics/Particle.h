
#pragma once

#include <Math/Vector3.h>

template <class T = float>
class Particle
{

public:
	//Member variables
	Vector3<> current;
	Vector3<> previous;
	Vector3<> acceleration;

	//Constructor
	Particle(const Vector3<>& curr, const Vector3<>& prev, const Vector3<> acc);

	//Destructor
	~Particle() = default;
};

#pragma once

#include "Particle.h"

class Constraint
{

public:
	//Member variables
	Particle* one;
	Particle* two;
	float length;

	//Constructor
	Constraint(Particle* on, Particle* tw);

	//Destructor
	~Constraint() = default;
};


#pragma once

#include "Particle.h"

class Constraint
{

  public:
	//Member variables
	unsigned int one;
	unsigned int two;
	float length;

	//Constructor
	Constraint(unsigned int oneIndex, unsigned int twoIndex, float len);

	//Destructor
	~Constraint() = default;
};

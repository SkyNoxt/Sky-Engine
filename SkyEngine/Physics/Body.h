
#pragma once

#include "Constraint.h"

class Body
{
public:
	//Member variables
	unsigned int numParticles;
	unsigned int numConstraints;

	Particle* particleArray;
	Constraint* constraintArray;

	//Constructor
	Body(unsigned int particleCount, unsigned int constraintCount, Particle* particles, Constraint* constraints);

	//Member function
	void update(float squaredTimestep);

	//Destructor
	~Body();
};

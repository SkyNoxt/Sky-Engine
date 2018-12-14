
#pragma once

#include "Particle.h"

template <class T = float>
class Constraint
{

public:
	//Member variables
	Particle<>* one;
	Particle<>* two;
	T length;

	//Constructor
	Constraint(Particle<>* on, Particle<>* tw);

	//Member function
	void apply() const;

	//Destructor
	~Constraint() = default;
};

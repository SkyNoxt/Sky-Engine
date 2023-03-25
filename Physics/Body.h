
#pragma once

#include "Constraint.h"

class Body
{
  public:
	// Member variables
	unsigned int numParticles;
	unsigned int numConstraints;

	Particle* particleArray;
	Constraint* constraintArray;

	// Constructor
	Body(unsigned int particleCount, unsigned int constraintCount, Particle* particles, Constraint* constraints);

	// Member functions
	void update(float squaredTimestep);

	const Particle& particle(unsigned int index) const;
	Particle& particle(unsigned int index);

	const Constraint& constraint(unsigned int index) const;
	Constraint& constraint(unsigned int index);

	bool collision(const Body& body, float& collisionLength, Vector3<>& collisionVector, Particle& collisionParticle, Constraint& collisionConstraint);

	// Destructor
	~Body();

  private:
	void project(const Vector3<>& axis, float& min, float& max) const;
};

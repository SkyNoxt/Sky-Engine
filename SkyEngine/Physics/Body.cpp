
#include "Body.h"

Body::Body(unsigned int particleCount, unsigned int constraintCount, Particle* particles, Constraint* constraints)
	: numParticles(particleCount)
	, numConstraints(constraintCount)
	, particleArray(particles)
	, constraintArray(constraints)
{
}

void Body::update(float squaredTimestep)
{
	for(unsigned int i = 0; i < numParticles; ++i)
		{
			Particle& currentParticle = particle(i);
			Vector3<> current = currentParticle.current;

			currentParticle.current = current + current - currentParticle.previous + currentParticle.acceleration * squaredTimestep;
			currentParticle.previous = current;
		}
        
	for(unsigned int i = 0; i < numConstraints; ++i)
		{
			const Constraint& currentConstraint = constraint(i);
			Particle& one = particle(currentConstraint.one);
			Particle& two = particle(currentConstraint.two);

			Vector3<> vector = two.current - one.current;

			float len = vector.length();
			vector *= ((len - constraintArray[i].length) / len) * 0.5;

			one.current += vector;
			two.current -= vector;
		}
}

Body::~Body()
{
	delete[] particleArray;
	delete[] constraintArray;
}

const Particle& Body::particle(unsigned int index) const
{
	return particleArray[index];
}

Particle& Body::particle(unsigned int index)
{
	return particleArray[index];
}

const Constraint& Body::constraint(unsigned int index) const
{
	return constraintArray[index];
}

Constraint& Body::constraint(unsigned int index)
{
	return constraintArray[index];
}

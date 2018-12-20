
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
	Particle* particle;
	Vector3<> current;
	Vector3<> previous;

	Vector3<> velocity;
	Vector3<> newPosition;
	for(unsigned int i = 0; i < numParticles; ++i)
		{
			particle = particleArray + i;
			current = particle->current;
			previous = particle->previous;

			velocity = current - previous;
			newPosition = current + velocity + particle->acceleration * squaredTimestep;
			particle->previous = current;
			particle->current = newPosition;
		}

	Particle* one;
	Particle* two;
	Constraint* constraint;

	Vector3<> vector;
	for(unsigned int i = 0; i < numConstraints; ++i)
		{
			constraint = constraintArray + i;
			one = particleArray + constraint->one;
			two = particleArray + constraint->two;

			vector = two->current - one->current;

			float len = vector.length();
			vector *= ((len - constraintArray[i].length) / len) * 0.5;

			one->current += vector;
			two->current -= vector;
		}
}

Body::~Body()
{
	delete[] particleArray;
	delete[] constraintArray;
}

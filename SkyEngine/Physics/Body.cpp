
#include <cmath>

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

#include <iostream>

bool Body::collision(const Body& body, float& collisionLength, Vector3<>& collisionVector, Particle& collisionParticle, Constraint& collisionConstraint)
{
	float minDistance = 10000.0;

	for(unsigned int i = 0; i < numConstraints; ++i)
		{
			Constraint* constraint = constraintArray + i;
			Particle* one = particleArray + constraint->one;
			Particle* two = particleArray + constraint->two;

			//Calculate the axis perpendicular to this edge and normalize it
			Vector3<> axis = (two->current - one->current).cross(Vector3<> { 0, 1, 0 }).normalize();
			std::cout << axis.x << " " << axis.y << " " << axis.z << std::endl;
			float minA, minB, maxA, maxB; //Project both bodies onto the perpendicular axis

			project(axis, minA, maxA);
			body.project(axis, minB, maxB);

			//Calculate the distance between the two intervals
			float distance = minA < minB ? minB - maxA : minA - maxB;

			if(distance > 0.0f) //If the intervals don't overlap, return, since there is no collision
				return false;
			else if(std::abs(distance) < minDistance)
				{
					minDistance = std::abs(distance);
					collisionVector = axis;
					collisionConstraint = *constraint;
				}
		}

	/*for(unsigned int i = 0; i < body.numConstraints; ++i)
		{
			Constraint* constraint = body.constraintArray + i;
			Particle* one = body.particleArray + constraint->one;
			Particle* two = body.particleArray + constraint->two;

			//Calculate the axis perpendicular to this edge and normalize it
			Vector3<> axis = (two->current - one->current).cross(Vector3<> { 0, 1, 0 }).normalize();

			float minA, minB, maxA, maxB; //Project both bodies onto the perpendicular axis

			project(axis, minA, maxA);
			body.project(axis, minB, maxB);

			//Calculate the distance between the two intervals
			float distance = minA < minB ? minB - maxA : minA - maxB;

			if(distance > 0.0f) //If the intervals don't overlap, return, since there is no collision
				return false;
			else if(std::abs(distance) < minDistance)
				{
					minDistance = std::abs(distance);
					collisionVector = axis;
					collisionConstraint = *constraint;
				}
		}*/

	collisionLength = minDistance;

	/*-------------------------------------*/

	float SmallestD = 10000.0f; //Initialize the smallest distance to a high value

	for(unsigned int i = 0; i < numParticles; ++i)
		{
			//Measure the distance of the vertex from the line using the line equation
			float Distance = collisionVector.dot(particleArray[i].current);

			//If the measured distance is smaller than the smallest distance reported
			//so far, set the smallest distance and the collision vertex
			if(Distance < SmallestD)
				{
					SmallestD = Distance;
					collisionParticle = particleArray[i];
				}
		}

	/*-------------------------------------*/

	return true; //There is no separating axis. Report a collision!
}

void Body::project(const Vector3<>& axis, float& min, float& max) const
{
	float dot = axis.dot(particleArray[0].current);

	min = max = dot;

	for(unsigned int i = 1; i < numParticles; ++i)
		{
			dot = axis.dot(particleArray[i].current);
			min = dot < min ? dot : min;
			max = dot > max ? dot : max;
		}
}

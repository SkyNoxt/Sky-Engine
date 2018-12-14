
#include <Math/Vector3.h>

#include "Constraint.h"

template <class T>
Constraint<T>::Constraint(Particle<>* on, Particle<>* tw)
	: one(on)
	, two(tw)
	, length(two->current.distance(one->current))
{
}

template <class T>
void Constraint<T>::apply() const
{
	Vector3<> vector = two->current - one->current;

	float len = vector.length();
	float diff = len - length;

	vector = vector.normalize();

	one->current += vector * diff * 0.5f;
	two->current -= vector * diff * 0.5f;
}

template class Constraint<>;

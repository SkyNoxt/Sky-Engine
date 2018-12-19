
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
	vector *= ((len - length) / len) * 0.5;

	one->current += vector;
	two->current -= vector;
}

template class Constraint<>;
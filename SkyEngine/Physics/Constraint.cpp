
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

	T l = 1 / len;

	if(l)
		vector = Vector3<T>{ vector.x * l, vector.y * l, vector.z * l };
	else
		vector = Vector3<T>{ 0, 0, 0 };

	one->current += vector * diff * 0.5f;
	two->current -= vector * diff * 0.5f;
}

template class Constraint<>;

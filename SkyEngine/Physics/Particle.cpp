
#include "Particle.h"

template <class T>
Particle<T>::Particle(const Vector3<>& curr, const Vector3<>& prev, const Vector3<> acc)
	: current(curr)
	, previous(prev)
	, acceleration(acc)
{
}

template class Particle<>;


#include "Constraint.h"

Constraint::Constraint(Particle* on, Particle* tw)
	: one(on)
	, two(tw)
	, length(two->current.distance(one->current))
{
}

void Constraint::apply() const
{
	Vector3<> vector = two->current - one->current;

	float len = vector.length();
	vector *= ((len - length) / len) * 0.5;

	one->current += vector;
	two->current -= vector;
}

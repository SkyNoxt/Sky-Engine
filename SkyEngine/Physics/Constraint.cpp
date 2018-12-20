
#include "Constraint.h"

Constraint::Constraint(Particle* on, Particle* tw)
	: one(on)
	, two(tw)
	, length(two->current.distance(one->current))
{
}

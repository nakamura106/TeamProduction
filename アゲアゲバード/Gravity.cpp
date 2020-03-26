#include "Gravity.h"

Gravity::Gravity()
{
	pos_y = 0.0f;
	t = 0.0f;
	v0 = 0.0f;
	g = 9.8f;
}

void Gravity::AddGravity(float pos_y_, float v0_)
{
	pos_y = pos_y_;
	v0 = v0_;

	pos_y += v0 * t + ((-g) * t * t) / 2.0f;

	t += 0.1f;
}
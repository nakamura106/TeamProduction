#include "Gravity.h"

Gravity::Gravity()
{
	pos_y = 0.0f;
	t = 0.0f;
	flame = 0.01666667;
	v0 = 0.0f;
	g = 9.8f;
}

void Gravity::ResetPalam()
{
	pos_y = 0.0f;
	t = 0.0f;
	flame = 0.01666667;
	v0 = 0.0f;
}

void Gravity::FreeFall(float pos_y_)
{
	pos_y = pos_y_;

	pos_y += (-g) * (t * t) / 2.0f;

	t += flame;
}

void Gravity::ThrowingUp(float pos_y_, float v0_)
{
	pos_y = pos_y_;
	v0 = v0_;

	pos_y += v0 * t + ((-g) * (t * t)) / 2.0f;

	t += flame;
}


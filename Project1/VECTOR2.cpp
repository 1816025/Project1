#include "VECTOR2.h"

VECTOR2::VECTOR2()
{
}

VECTOR2::VECTOR2(int x, int y)
{
	this->x = x;
	this->y = y;
}

VECTOR2::~VECTOR2()
{
}

int & VECTOR2::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

VECTOR2 operator/(const VECTOR2 & r, const VECTOR2 & l)
{
	VECTOR2 vec;
	vec.x = r.x / l.x;
	vec.y = r.y / l.y;
	return vec;
}

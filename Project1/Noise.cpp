#include <math.h>
#include "DxLib.h"
#include "Noise.h"

float Noise::ValueNoise(float x, float y)
{
	///�������Ə������ɕ���
	int xi = (int)floorf(x);
	int yi = (int)floorf(y);
	float xf = x - xi;
	float yf = x - yi;

	return 0.0f;
}

//���`���
float Noise::LineInterpolation(float a, float b, float x)
{
	return (a + (b - a) * x);
}

Noise::Noise()
{
}

Noise::~Noise()
{
}

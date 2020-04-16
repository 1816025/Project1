#pragma once
#include "VECTOR2.h"

#define lpNoise Noise &GetInstance();

class Noise
{
public:
	static Noise &GetInstance(void)
	{
		static Noise s_Instance;
		return s_Instance;
	}
	//float Grad();	//Œù”z
	float ValueNoise(float x, float y);		//ÊŞØ­°É²½Şæ“¾

	float LineInterpolation(float a,float b,float x);	//üŒ`•âŠÔ

private:
	Noise();
	~Noise();
};


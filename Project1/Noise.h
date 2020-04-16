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
	//float Grad();	//���z
	float ValueNoise(float x, float y);		//��ح�ɲ�ގ擾

	float LineInterpolation(float a,float b,float x);	//���`���

private:
	Noise();
	~Noise();
};


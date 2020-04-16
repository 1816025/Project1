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
	//float Grad();	//勾配
	float ValueNoise(float x, float y);		//ﾊﾞﾘｭｰﾉｲｽﾞ取得

	float LineInterpolation(float a,float b,float x);	//線形補間

private:
	Noise();
	~Noise();
};


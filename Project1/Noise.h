#pragma once
#include <array>
#include "VECTOR2.h"

#define lpNoise Noise::GetInstance()

#define HASH_CODE_MAX			(256)
#define HASH_CODE_TABLE_NUM		(HASH_CODE_MAX*2)

class Noise
{
public:
	static Noise &GetInstance(void)
	{
		static Noise s_Instance;
		return s_Instance;
	}
	float GetValue(int x,int y);
	float ValueNoise(float x, float y);		//ﾊﾞﾘｭｰﾉｲｽﾞ取得
	void SetHash(unsigned int seed);
	unsigned int GetHash(int x, int y);

	float LineInterpolation(float a,float b,float x);	//線形補間
	float CubicInterpolation(float x);	//キュービック補間

private:
	Noise();
	~Noise();
	std::array<int, HASH_CODE_TABLE_NUM> HashCode;
};


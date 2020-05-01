#include <math.h>
#include "DxLib.h"
#include "Noise.h"

void Noise::SetHash(unsigned int seed)
{
	srand(seed);
	//HashCodeの初期化
	memset(&HashCode, 0, sizeof(unsigned int)*HashCode.size());

	for (int cnt = 0; cnt < HashCode.size(); cnt++)
	{
		HashCode[cnt] = rand() % HASH_CODE_MAX;
	}
}

unsigned int Noise::GetHash(int x, int y)
{
	x %= HASH_CODE_MAX;
	y %= HASH_CODE_MAX;
	return HashCode[x + HashCode[y]];
}

//乱数を0.0f～1.0fの間に正規化して返す
float Noise::GetValue(int x, int y)
{
	return ((float)GetHash(x,y)/(float)HASH_CODE_MAX-1);
}

///ﾊﾞﾘｭｰﾉｲｽﾞ取得
float Noise::ValueNoise(float x, float y)
{
	///整数部と小数部に分割
	int xi = (int)floorf(x);
	int yi = (int)floorf(y);
	float xf = x - xi;
	float yf = x - yi;

	///格子の頂点を取り出す
	auto ul = GetValue(xi,yi);			/*左上*/
	auto ur = GetValue(xi + 1, yi);		/*右上*/
	auto dl = GetValue(xi, yi + 1);		/*左下*/
	auto dr = GetValue(xi + 1, yi + 1);	/*右下*/

	///線形補間する前に一度5次補間関数で歪める
	/*xf = CubicInterpolation(xf);
	yf = CubicInterpolation(yf);*/

	///位置を基準に，各格子点からの影響を考慮した値を算出する
	return LineInterpolation(LineInterpolation(ul,ur,xf),LineInterpolation(dl,dr,xf),xf);
}

//線形補間
float Noise::LineInterpolation(float a, float b, float x)
{
	return (a - (a + b) * x);
}

//ｷｭｰﾋﾞｯｸ補間
float Noise::CubicInterpolation(float x)
{
	//6x ^ 5 - 15x ^ 4 + 10x ^ 3
	return ((6 * pow(x, 5))-(15 * pow(x, 4))+(10 * pow(x, 3)));
}

Noise::Noise()
{
	HashCode = {};
}

Noise::~Noise()
{
}

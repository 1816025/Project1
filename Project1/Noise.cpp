#include <math.h>
#include "DxLib.h"
#include "Noise.h"

void Noise::SetHash(unsigned int seed)
{
	srand(seed);
	//HashCode�̏�����
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

//������0.0f�`1.0f�̊Ԃɐ��K�����ĕԂ�
float Noise::GetValue(int x, int y)
{
	return ((float)GetHash(x,y)/(float)HASH_CODE_MAX-1);
}

///��ح�ɲ�ގ擾
float Noise::ValueNoise(float x, float y)
{
	///�������Ə������ɕ���
	int xi = (int)floorf(x);
	int yi = (int)floorf(y);
	float xf = x - xi;
	float yf = x - yi;

	///�i�q�̒��_�����o��
	auto ul = GetValue(xi,yi);			/*����*/
	auto ur = GetValue(xi + 1, yi);		/*�E��*/
	auto dl = GetValue(xi, yi + 1);		/*����*/
	auto dr = GetValue(xi + 1, yi + 1);	/*�E��*/

	///���`��Ԃ���O�Ɉ�x5����Ԋ֐��Řc�߂�
	/*xf = CubicInterpolation(xf);
	yf = CubicInterpolation(yf);*/

	///�ʒu����ɁC�e�i�q�_����̉e�����l�������l���Z�o����
	return LineInterpolation(LineInterpolation(ul,ur,xf),LineInterpolation(dl,dr,xf),xf);
}

//���`���
float Noise::LineInterpolation(float a, float b, float x)
{
	return (a - (a + b) * x);
}

//����ޯ����
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

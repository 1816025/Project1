#pragma once
#include <array>
#define lpRaid Raid::GetInstance()

enum class Dir
{
	Forward,
	Recession,
	Left,
	Right,
	Max
};

class Raid
{
public:
	static Raid &GetInstance()
	{
		static Raid s_Instance;
		return s_Instance;
	}
	void UpDate(void);
	const int GetRepelCount(void);
private:
	Raid();
	~Raid();
	int LifePoint;
	int RepelCount;
	array<VECTOR2, (int)Dir::Max> Dir_Tbl;
};


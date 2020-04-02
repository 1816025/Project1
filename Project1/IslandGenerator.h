#pragma once
#include "BaseScene.h"
#define lpIslandGenerator IslandGenerator::GetInstance()
class IslandGenerator
{
public:
	static IslandGenerator &GetInstance(void)
	{
		static IslandGenerator s_Instance;
		return s_Instance;
	}
	void IslandMaker();
	void IslandInit();
private:
	IslandGenerator();
	~IslandGenerator();
};


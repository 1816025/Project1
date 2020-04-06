#pragma once
#include "MapCtl.h"


struct FactoryStatus
{
	int Flag;				//資源を生成できるか
	int ProductionSpeed;	//製造速度
	int Amount;				//1度に生成できる量
};

struct STOCK
{
	int Gold;
	int Iron;
	int Food;
	int Wood;
};

#define lpFactory Factory::GetInstance()

class Factory
{
public:
	static Factory &GetInstance(void)
	{
		static Factory s_Instance;
		return s_Instance;
	}
	void UpDate(void);
	void Draw();
	STOCK GetStockPile(void);
private:
	Factory();
	~Factory();
	array<FactoryStatus,static_cast<size_t>(Map_ID::water)>status;
	STOCK Stockpile;
};


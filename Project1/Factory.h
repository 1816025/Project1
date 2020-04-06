#pragma once
#include "MapCtl.h"


struct FactoryStatus
{
	int Flag;				//�����𐶐��ł��邩
	int ProductionSpeed;	//�������x
	int Amount;				//1�x�ɐ����ł����
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


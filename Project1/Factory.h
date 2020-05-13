#pragma once
#include "MapCtl.h"

class Game;

struct FactoryStatus
{
	int Flag;				//éëåπÇê∂ê¨Ç≈Ç´ÇÈÇ©
	int ProductionSpeed;	//êªë¢ë¨ìx
	int Amount;				//1ìxÇ…ê∂ê¨Ç≈Ç´ÇÈó 
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
	void UpDate(Date);
	void Draw();
	STOCK GetStockPile(void);
	void SetStockPile(int food ,int Gold,int Iron , int Wood);
private:
	Factory();
	~Factory();
	array<FactoryStatus,static_cast<size_t>(Map_ID::water)>status;
	STOCK Stockpile;
};


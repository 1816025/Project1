#include "DxLib.h"
#include "Factory.h"

Factory::Factory()
{
	Stockpile = { 0,0,0,0 };
	status = 
	{
		true,60,2,
		true,60,5,
		true,60,5
	};
}

Factory::~Factory()
{
}

void Factory::Draw()
{
	DrawFormatString(300, 680, 0xffffff, "Stockpile.Gold: %d", Stockpile.Gold);
	DrawFormatString(300, 700, 0xffffff, "Stockpile.Food: %d", Stockpile.Food);
	DrawFormatString(300, 720, 0xffffff, "Stockpile.Wood: %d", Stockpile.Wood);
}

void Factory::UpDate(void)
{
	Stockpile.Gold += (status[0].Flag == true ? status[0].Amount * lpMapCtl.GetPanelConter(Map_ID::mine) : 0);
	Stockpile.Food += (status[1].Flag == true ? status[1].Amount * lpMapCtl.GetPanelConter(Map_ID::field) : 0);
	Stockpile.Wood += (status[2].Flag == true ? status[2].Amount * lpMapCtl.GetPanelConter(Map_ID::hut) : 0);
}

STOCK Factory::GetStockPile(void)
{
	return Stockpile;
}

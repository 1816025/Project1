#include "DxLib.h"
#include "Game.h"
#include "Event.h"
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
	DrawFormatString(350, 680, 0xffffff, "Stockpile.Gold: %d", Stockpile.Gold);
	DrawFormatString(350, 700, 0xffffff, "Stockpile.Food: %d", Stockpile.Food);
	DrawFormatString(350, 720, 0xffffff, "Stockpile.Wood: %d", Stockpile.Wood);
}

void Factory::UpDate(Date date)
{
	if (lpEvent.GetEvent().id != EVENT::AbnormalWeather)
	{
		if (date.season == Season::winter)
		{
			Stockpile.Food += (status[1].Flag == true ? (status[1].Amount * lpMapCtl.GetPanelConter(Map_ID::field))*0.5 : 0);
		}
		else
		{
			if (date.weather == Weather::Rain)
			{
				Stockpile.Food += (status[1].Flag == true ? (status[1].Amount * lpMapCtl.GetPanelConter(Map_ID::field))*1.5 : 0);
			}
			else
			{
				Stockpile.Food += (status[1].Flag == true ? status[1].Amount * lpMapCtl.GetPanelConter(Map_ID::field) : 0);
			}
		}
	}

	Stockpile.Wood += (status[2].Flag == true ? status[2].Amount * lpMapCtl.GetPanelConter(Map_ID::hut) : 0);
	Stockpile.Gold += (status[0].Flag == true ? status[0].Amount * lpMapCtl.GetPanelConter(Map_ID::mine) : 0);
}

STOCK Factory::GetStockPile(void)
{
	return Stockpile;
}

void Factory::SetStockPile(int food, int gold, int iron, int wood)
{
	Stockpile.Food += food;
	Stockpile.Gold += gold;
	Stockpile.Iron += iron;
	Stockpile.Wood += wood;
}

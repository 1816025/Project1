#pragma once
#include "BaseScene.h"
#include "KeyCtl.h"

#define DisplaySizeX 600
#define DisplaySizeY 600
#define ChipSize 10

struct Date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
};

class Game:
	public BaseScene
{
public:
	Game();
	~Game();
	unique_base UpDate(unique_base own,const KeyCtl &controller);
private:
	int Init();
	void Timer(const KeyCtl &controller);	//¹Þ°Ñ“àŽžŠÔ‚ÆÌÚ°Ñ‚ÌŒv‘ª
	void Draw();
	bool TimeTransFlag;
	int Frame;
	Date date;
	bool Debug;
};


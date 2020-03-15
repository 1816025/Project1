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
	void Timer(const KeyCtl &controller);	//ｹﾞｰﾑ内時間とﾌﾚｰﾑの計測
	void Draw();
	bool TimeTransFlag;
	int Frame;
	Date date;
	bool Debug;
};


#pragma once
#include "BaseScene.h"
#include "MAP_ID.h"
#include "KeyCtl.h"

struct Date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
};

using namespace std;
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
	int seed;
	Date date;
	bool Debug;
	string WorldName;
	Map_ID id;
};


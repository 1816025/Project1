#pragma once
#include <map>
#include "VECTOR2.h"
#include "BaseScene.h"
#include "MAP_ID.h"
#include "KeyCtl.h"

enum class Season
{
	spring,
	summer,
	autumn,
	winter,
	max
};
enum class Weather
{
	Sunny,
	Cloudy,
	Rain,
	Snow,
	Storm,
	Blizzard,
	max
};
struct Date
{
	Season season;		//現在の季節
	Weather weather;	//現在の天気
	int cainWeather;	//何時間同じ天気が続いたか
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
	Game(string WorldName);
	~Game();
	unique_base UpDate(unique_base own,const KeyCtl &controller);
private:
	int Init(void);
	void Timer(const KeyCtl &controller);	//ｹﾞｰﾑ内時間とﾌﾚｰﾑの計測
	void SetWeather(Season season);					//天候の操作
	void Draw(void);
	bool TimeTransFlag;
	int Frame;
	int CntSpeed;
	int seed;
	Date date;
	bool Debug;
	string WorldName;
	Map_ID id;
	map<string, VECTOR2> IconSize;
};


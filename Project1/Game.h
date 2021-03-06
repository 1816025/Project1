#pragma once
#include <map>
#include "VECTOR2.h"
#include "BaseScene.h"
#include "MAP_ID.h"
enum class DayCycle
{
	Day,
	Night,
	Max
};
struct Date
{
	DayCycle daycycle;
	int year;
	int month;
	int day;
	int hour;
	int minute;
};
class  KeyCtl;

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
	void Draw(void);
	void  Phase(DayCycle cycle);

	bool OpenFlag;
	bool TimeTransFlag;
	bool OptionFlag;
	bool SetObjectFlag;
	int Frame;
	int CntSpeed;
	int seed;
	int BookCnt;
	int WorldRank;
	int CollectCnt;
	Date date;
	bool Pose;
	string WorldName;
	Map_ID id;
	map<string, VECTOR2> ImageSize;
	map<string, int>fontHandle;
};


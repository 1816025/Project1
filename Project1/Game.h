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
	Season season;		//���݂̋G��
	Weather weather;	//���݂̓V�C
	int cainWeather;	//�����ԓ����V�C����������
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
	void Timer(const KeyCtl &controller);	//�ްѓ����Ԃ��ڰт̌v��
	void SetWeather(Season season);					//�V��̑���
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


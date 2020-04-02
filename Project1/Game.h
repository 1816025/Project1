#pragma once
#include "BaseScene.h"
#include "KeyCtl.h"

#define lpGame Game::GetInstance()

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
	static Game &GetInstance(void)
	{
		static Game s_Instance;
		return s_Instance;
	}
	unique_base UpDate(unique_base own,const KeyCtl &controller);
	const Date Getdate();
private:
	Game();
	~Game();
	int Init();
	void Timer(const KeyCtl &controller);	//¹Þ°Ñ“àŽžŠÔ‚ÆÌÚ°Ñ‚ÌŒv‘ª
	void Draw();
	bool TimeTransFlag;
	int Frame;
	int seed;
	Date date;
	bool Debug;
};


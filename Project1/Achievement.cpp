#include "DxLib.h"
#include "OverLoad.h"
#include "Achievement.h"

Achievement::Achievement()
{
	AchievementList = 
	{
		"本日開館",
		"本日休館日",
		"開館一周年",
		"開館五周年",
		"本取集５回",
		"本取集10回"
	};
	AchievementData["本日開館"]   = {false,{DayCycle::Day,0,1,1,0,0},0,0, 0};
	AchievementData["本日休館日"] = {false,{DayCycle::Day,0,4,1,0,0},0,0, 0};
	AchievementData["開館一周年"] = {false,{DayCycle::Day,2,1,1,0,0},0,0, 0};
	AchievementData["開館五周年"] = {false,{DayCycle::Day,6,1,1,0,0},0,0, 0};
	AchievementData["本取集５回"] = {false,{DayCycle::Day,0,1,1,0,0},0,0, 5};
	AchievementData["本取集10回"] = {false,{DayCycle::Day,0,1,1,0,0},0,0,10};
}

Achievement::~Achievement()
{
}

void Achievement::UpDate(string key, AchievementStatus status)
{
	if (AchievementData[key].flag == false)
	{
		if (status >= AchievementData[key])
		{
			AchievementData[key].flag = true;
		}
	}
}

AchievementTbl Achievement::GetAchievement(void)
{
	return AchievementList;
}

AchievementStatus Achievement::GetAchievementData(string key)
{
	return AchievementData[key];
}


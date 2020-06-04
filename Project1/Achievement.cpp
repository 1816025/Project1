#include "DxLib.h"
#include "OverLoad.h"
#include "Achievement.h"

Achievement::Achievement()
{
	AchievementList = 
	{
		"�{���J��",
		"�{���x�ٓ�",
		"�J�و���N",
		"�J�ٌ܎��N",
		"�{��W�T��",
		"�{��W10��"
	};
	AchievementData["�{���J��"]   = {false,{DayCycle::Day,0,1,1,0,0},0,0, 0};
	AchievementData["�{���x�ٓ�"] = {false,{DayCycle::Day,0,4,1,0,0},0,0, 0};
	AchievementData["�J�و���N"] = {false,{DayCycle::Day,2,1,1,0,0},0,0, 0};
	AchievementData["�J�ٌ܎��N"] = {false,{DayCycle::Day,6,1,1,0,0},0,0, 0};
	AchievementData["�{��W�T��"] = {false,{DayCycle::Day,0,1,1,0,0},0,0, 5};
	AchievementData["�{��W10��"] = {false,{DayCycle::Day,0,1,1,0,0},0,0,10};
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


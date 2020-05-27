#pragma once
#include <map>
#include <array>
#include <string>
#include "Game.h"

#define lpAchievement Achievement::GetInstance()
using namespace std;
struct AchievementStatus
{
	bool flag;					//’B¬‚µ‚½‚©
	//‰ğ•úğŒ
	Date date;
	int BookRank;
	int BookCnt;
	int CollectCnt;
};
using AchievementTbl = array<string, 6>;
class Achievement
{
public:
	static Achievement &GetInstance()
	{
		static Achievement s_Instance;
		return s_Instance;
	}
	void UpDate(string key,AchievementStatus status);
	AchievementTbl GetAchievement(void);
	AchievementStatus GetAchievementData(string key);
private:
	Achievement();
	~Achievement();
	map<string, AchievementStatus>AchievementData;
	AchievementTbl AchievementList;

};


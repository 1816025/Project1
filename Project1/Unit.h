#pragma once
#include <vector>
#include "VECTOR2.h"

#define lpUnit Unit::GetInstance()
enum class GroupStatus
{
	ALLY,		//’‡ŠÔ
	ACTIVE,		//“G‘Î¶•¨(“G‘Îó‘Ô)
	NON,
	MAX
};

enum class GroupName
{
	HUMAN,
	BEAR,
	SNAKE,
	WOLF,
	MAX
};

struct GroupParameter
{
	GroupStatus Status;		//“G–¡•û‚Ì¯•Ê
	int Lp;					//‘Ì—Í
	int Ap;					//UŒ‚—Í
	int As;					//UŒ‚‘¬“x
	VECTOR2 pos;			//À•W
};
using namespace std;
class Unit
{
public:
	static Unit& GetInstance()
	{
		static Unit s_Instance;
		return s_Instance;
	}
	void UpDate(void);
	void SetPos(VECTOR2 pos, int index);
	VECTOR2 GetPos(int index);
	const vector<GroupParameter> GetUnitList();	
	const GroupParameter GetUnitList(int index);

	const int GetUnitStatus(VECTOR2 pos);	//‚»‚ÌÀ•W‚É‘¶İ‚·‚éƒ†ƒjƒbƒg‚ª‚Ç‚Ì‚æ‚¤‚È‘¶İ‚©‚ğ•Ô‚·

	void BattlePhase(int index, int enemy_index);		//ƒ†ƒjƒbƒg‚ªo‰ï‚¤‚ÆŒÄ‚Î‚ê‚é
	void EndPhase(int index, int enemy_index);			//Ÿ”s‚ªŒˆ‚Ü‚é‚ÆŒÄ‚Î‚ê‚é
	void PopPhase(GroupParameter param);			    //Ÿ”s‚ªŒˆ‚Ü‚é‚ÆŒÄ‚Î‚ê‚é

private:
	Unit();
	~Unit();

	vector<GroupParameter> UnitList;	//“G‚©–¡•û‚©‚ğ“ü‚ê‚Ä‚¨‚­
};


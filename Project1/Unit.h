#pragma once
#include <vector>
#include "VECTOR2.h"

#define lpUnit Unit::GetInstance()
enum class GroupStatus
{
	ALLY,		//仲間
	ACTIVE,		//敵対生物(敵対状態)
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
	GroupStatus Status;		//敵味方の識別
	int Lp;					//体力
	int Ap;					//攻撃力
	int As;					//攻撃速度
	VECTOR2 pos;			//座標
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

	const int GetUnitStatus(VECTOR2 pos);	//その座標に存在するユニットがどのような存在かを返す

	void BattlePhase(int index, int enemy_index);		//ユニットが出会うと呼ばれる
	void EndPhase(int index, int enemy_index);			//勝敗が決まると呼ばれる
	void PopPhase(GroupParameter param);			    //勝敗が決まると呼ばれる

private:
	Unit();
	~Unit();

	vector<GroupParameter> UnitList;	//敵か味方かを入れておく
};


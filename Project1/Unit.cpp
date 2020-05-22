#include "Unit.h"

Unit::Unit()
{
}
Unit::~Unit()
{
}

void Unit::UpDate(void)
{

}

void Unit::SetPos(VECTOR2 pos, int index)
{
	UnitList[index].pos = pos;
}

VECTOR2 Unit::GetPos(int index)
{
	return UnitList[index].pos;
}

const vector<GroupParameter> Unit::GetUnitList()
{
	return UnitList;
}

const int Unit::GetUnitStatus(VECTOR2 pos)
{
	auto itr = UnitList.begin();
	itr = find(itr, UnitList.end(), pos);
	return distance(UnitList.begin(),itr);
}

void Unit::BattlePhase(int index, int enemy_index)
{
	if (UnitList[index].Lp > 0 || UnitList[enemy_index].Lp > 0)
	{
		if (UnitList[index].As <= 0)
		{
			UnitList[enemy_index].Lp -= UnitList[index].Ap;
			UnitList[index].As = 10;
		}
		if (UnitList[enemy_index].As <= 0)
		{
			UnitList[index].Lp -= UnitList[enemy_index].Ap;
			UnitList[enemy_index].As = 10;
		}
		UnitList[index].As--;
		UnitList[enemy_index].As--;
	}
	else
	{
		if (UnitList[enemy_index].Lp <= 0)
		{
			EndPhase(index, enemy_index);
		}

		if (UnitList[index].Lp <= 0)
		{
			EndPhase(enemy_index, index);
		}
	}
}

void Unit::EndPhase(int winer_param, int loser_param)
{
	UnitList.erase(UnitList.begin() + loser_param);
}

void Unit::PopPhase(GroupParameter index)
{
	UnitList.emplace_back(index);
}


#include "DxLib.h"
#include "Event.h"
#include "BookList.h"
#include "MapCtl.h"
#include "Unit.h"
#include "Raid.h"

void Raid::UpDate(void)
{
	GroupParameter param = { GroupStatus::ACTIVE, 100,10,10,VECTOR2(0,0) };
	lpUnit.PopPhase(param);



	/*
	if (LifePoint > 0)
	{
		auto dir = rand() % (int)Dir::Max;
		for (int index = 0; lpUnit.GetUnitList().size(); index++)
		{
			if (lpUnit.GetUnitList().size() <= index)
			{
				break;
			}
			if (lpUnit.GetUnitList(index).Status == GroupStatus::ACTIVE)
			{
				auto tmppos = lpUnit.GetPos(index) + Dir_Tbl[dir];
				auto id = lpMapCtl.GetMapData(tmppos);
				auto tmpindex = lpUnit.GetUnitStatus(tmppos);
				auto tmpstatus = lpUnit.GetUnitList(tmpindex).Status;
				switch (id)
				{
				case Map_ID::BOOK_SHELF:
				case Map_ID::COUNTER:
				case Map_ID::DESK:
				case Map_ID::CHAIR:
					lpUnit.SetPos(lpUnit.GetPos(index) + Dir_Tbl[(int)Dir::Right], index);
					break;
				case Map_ID::NON:
						if (lpUnit.GetUnitList(tmpindex).Status == GroupStatus::ALLY)
						{
							lpUnit.BattlePhase(tmpindex, index);
						}
						else
						{
							lpUnit.SetPos(lpUnit.GetPos(index) + Dir_Tbl[dir], index);
						}
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		lpEvent.SetEvent(false, EVENT::Debut);
		lpBookList.SetLooting(lpBookList.GetArchive(rand() % lpBookList.GetArchiveSize()), false);
	}*/
}

const int Raid::GetRepelCount(void)
{
	return RepelCount;
}

Raid::~Raid()
{
}
Raid::Raid()
{
	Dir_Tbl = { VECTOR2(0,-1),VECTOR2(0,1),VECTOR2(-1,0),VECTOR2(1,0) };
	LifePoint = 10;
}

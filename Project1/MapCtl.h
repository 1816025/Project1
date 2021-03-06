#pragma once
#include <array>
#include <vector>
#include "Game.h"
#include "MAP_ID.h"
#include "DxLib.h"
#include "vector2.h"

struct Status
{
	bool BuildFlag;
	bool MoveFlag;
};

#define lpMapCtl MapCtl::GetInstance()

using namespace std;

class Game;

struct CheackSize
{
	bool operator()(const VECTOR2& selPos, const VECTOR2& mapSize)
	{
		if ((selPos.x < 0) || (selPos.x >= mapSize.x)
			|| (selPos.y < 0) || (selPos.y >= mapSize.y))
		{
			return false;
		}
		return true;
	}
};

class MapCtl
{
public:
	static MapCtl &GetInstance(void)
	{
		static MapCtl s_Instance;
		return s_Instance;
	}

	bool MapSave(bool first,string worldname = "New World");
	bool MapLoad(string worldname);

	bool SetUp(const VECTOR2& size, const VECTOR2& chipSize, const VECTOR2& offSet);
	bool SetMapData(const VECTOR2& pos,Map_ID id);
	Map_ID GetMapData(const VECTOR2& pos);
	Status GetPanelStatus(const VECTOR2& pos);
	int GetPanelConter(const Map_ID id);
	void Draw(void);
	void SetPos(VECTOR2 pos);
	void SetDate(Date date);
private:
	MapCtl();
	~MapCtl();
	vector<Map_ID>MapDataBace;
	vector<Map_ID*>MapData;
	Status PanelStatus;
	array<Status, static_cast<size_t>(Map_ID::MAX)>color;
	VECTOR2 mapSize;
	VECTOR2 chipsize;
	VECTOR2 drawOffset;
	VECTOR2 pos;
	Date date;

	string WorldName;
};


#pragma once
#include <array>
#include <vector>
#include "DxLib.h"
#include "vector2.h"

enum class Map_ID
{
	water,
	water2,
	plain,
	rock,
	sand,
	forest,
	NON,
	MAX
};

#define lpMapCtl MapCtl::GetInstance()

using namespace std;

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

	bool SetUp(const VECTOR2& size, const VECTOR2& chipSize, const VECTOR2& offSet);
	bool SetMapData(const VECTOR2& pos,Map_ID id);
	Map_ID GetMapData(const VECTOR2& pos);
	void Draw(void);
	void SetPos(VECTOR2 pos);
private:
	MapCtl();
	~MapCtl();
	vector<Map_ID>MapDataBace;
	vector<Map_ID*>MapData;
	array<int, static_cast<size_t>(Map_ID::MAX)>color;
	VECTOR2 mapSize;
	VECTOR2 chipsize;
	VECTOR2 drawOffset;
	VECTOR2 pos;
};


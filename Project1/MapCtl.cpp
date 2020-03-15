#include "VECTOR2.h"
#include "Game.h"
#include "MapCtl.h"

bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipSize, const VECTOR2 & offSet)
{
	this->mapSize = VECTOR2(size.x/chipSize.x,size.y/chipSize.y);
	this->chipsize = chipSize;
	drawOffset = offSet;
	MapDataBace.resize(mapSize.x * mapSize.y);
	MapData.resize(mapSize.y);
	for (int count = 0; count < MapData.size(); count++)
	{
		MapData[count] = &MapDataBace[mapSize.x * count];
	}
	for (int j = 0; j < MapDataBace.size(); j++)
	{
		MapDataBace[j] = Map_ID::water;
	}
	return false;
}

bool MapCtl::SetMapData(const VECTOR2 & pos, Map_ID id)
{
	VECTOR2 selPos(pos / chipsize);
	if (!CheackSize()(selPos, mapSize))
	{
		return false;
	}
	MapData[selPos.y][selPos.x] = id;
	return true;
}

Map_ID MapCtl::GetMapData(const VECTOR2 & pos)
{
	VECTOR2 selPos(pos / chipsize);
	if (!CheackSize()(selPos, mapSize))
	{
		return Map_ID::NON;
	}
	return MapData[selPos.y][selPos.x];
}

void MapCtl::Draw(void)
{
	for (int y = 0;y< DisplaySizeY / ChipSize; y++)
	{
		for (int x = 0;x< DisplaySizeX / ChipSize; x++)
		{
			Map_ID id = MapData[y][x];
			DrawBox(drawOffset.x + chipsize.x*x, drawOffset.y + chipsize.y*y,drawOffset.x + chipsize.x*x + ChipSize, drawOffset.y + chipsize.y*y + ChipSize,color[static_cast<int>(id)],true);
		}
	}
}


void MapCtl::SetPos(VECTOR2 pos)
{
}
MapCtl::MapCtl()
{
	color =
	{
		0x0000ff,
		0x000080,
		0x00ff00,
		0xc0c0c0,
		0xFFFFBB,
		0x005500,
		0xffffff
	};
}
MapCtl::~MapCtl()
{
}

#include <string>
#include <sys/stat.h>
#include "VECTOR2.h"
#include "ImageMng.h"
#include "MAP_ID.h"
#include "Game.h"
#include "MapCtl.h"
struct  DataHeader
{
	int WorldName;
	int Frame;
	Date date;
	int sizeX;
	int sizeY;
};
bool MapCtl::MapSave(bool first, string worldname)
{
	string WorldName = "data/" + worldname + ".map";
	DataHeader expData
	{
		atoi(worldname.c_str()),
		0,
		date,
		mapSize.x,
		mapSize.y
	};
	struct stat statBuf;
	FILE *file;
	fopen_s(&file, WorldName.c_str(), "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fwrite(&MapDataBace[0], sizeof(Map_ID)*MapDataBace.size(), 1, file);
	fclose(file);

	return true;
}

bool MapCtl::MapLoad(string worldname)
{
	string WorldName = "data/" + worldname.erase(worldname.find(".")) + ".map";
	FILE *file;
	DataHeader expData;
	fopen_s(&file, WorldName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	MapDataBace.resize(expData.sizeX * expData.sizeY);
	fread(&MapDataBace[0], sizeof(Map_ID), MapDataBace.size(), file);
	this->WorldName = worldname;
	fclose(file);
	return true;
}

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
		MapDataBace[j] = Map_ID::water2;
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

Status MapCtl::GetPanelStatus(const VECTOR2 & pos)
{
	VECTOR2 selPos(pos / chipsize);
	if (!CheackSize()(selPos, mapSize))
	{
		return color[static_cast<int>(Map_ID::NON)] ;
	}
		Map_ID id = MapData[selPos.y][selPos.x];
	return color[static_cast<int>(id)];
}

int MapCtl::GetPanelConter(const Map_ID id)
{
	int cnt = 0;
	for (int y = 0; y < DisplaySizeY / ChipSize; y++)
	{
		for (int x = 0; x < DisplaySizeX / ChipSize; x++)
		{
			cnt += (id == MapData[y][x] ? 1 : 0);
		}
	}
	return cnt;
}

void MapCtl::Draw(void)
{
	for (int y = 0;y< DisplaySizeY / ChipSize; y++)
	{
		for (int x = 0;x< DisplaySizeX / ChipSize; x++)
		{
			Map_ID id = MapData[y][x];

			DrawGraph(drawOffset.x + chipsize.x*x, drawOffset.y + chipsize.y*y, lpImageMng.GetID("img/panel.png", VECTOR2(10, 10), VECTOR2(5, 2))[static_cast<int>(id)], false);
		}
	}
}


void MapCtl::SetPos(VECTOR2 pos)
{
}
void MapCtl::SetDate(Date date)
{
	this->date = date;
}
MapCtl::MapCtl()
{
	color =
	{
		/*êlçHï®*/
		false,false,
		false,false,
		false,false,
		/*é©ëRê∂ê¨ï®*/
		false,true,
		false,true,
		true,false,
		true,false,
		true,false,
		false,false,
		false,false
	};
}
MapCtl::~MapCtl()
{
}

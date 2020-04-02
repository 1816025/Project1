#include "VECTOR2.h"
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
bool MapCtl::MapSave(string worldname = "NewWorld")
{
	string WorldName = "data/" + worldname + ".map";
	DataHeader expData
	{
		atoi(worldname.c_str()),
		0,
		lpGame.Getdate(),
		mapSize.x,
		mapSize.y
	};
	FILE *file;
	fopen_s(&file,WorldName.c_str(), "wb");
	fwrite(&expData, sizeof(expData), 1, file);
	fwrite(&MapDataBace[0], sizeof(Map_ID)*MapDataBace.size(), 1, file);
	fclose(file);
	return true;
	return false;
}

bool MapCtl::MapLoad(void)
{
	return false;
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

void MapCtl::Draw(void)
{
	for (int y = 0;y< DisplaySizeY / ChipSize; y++)
	{
		for (int x = 0;x< DisplaySizeX / ChipSize; x++)
		{
			Map_ID id = MapData[y][x];

			DrawBox(drawOffset.x + chipsize.x*x, drawOffset.y + chipsize.y*y,drawOffset.x + chipsize.x*x + ChipSize, drawOffset.y + chipsize.y*y + ChipSize,static_cast<int>(color[static_cast<int>(id)].color),true);
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
		0x0000ff,0,0,0,Biome::Ocean,true,
		0x0000a0,0,0,0,Biome::Ocean,true,
		0x00ff00,0,1,0,Biome::Plain,true,
		0xc0c0c0,0,1,0,Biome::Mountain,true,
		0xFFFFBB,0,1,0,Biome::Desert,true,
		0x005500,0,1,0,Biome::Forest,true,
		0xffffff,0,1,0,Biome::Ocean,true,
	};
}
MapCtl::~MapCtl()
{
}

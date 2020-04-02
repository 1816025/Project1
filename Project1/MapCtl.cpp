#include <string>
#include <sys/stat.h>
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
bool MapCtl::MapSave(bool first,string worldname)
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
	if (first == true && stat(WorldName.c_str(), &statBuf) == 0)
	{
		int onButton = MessageBox(NULL, "YES: 上書き NO: 新規保存", "同じファイル名ですが上書きしてもよろしいですか？", MB_YESNO);
		if (onButton == IDYES)
		{
			fopen_s(&file, WorldName.c_str(), "wb");
			fwrite(&expData, sizeof(expData), 1, file);
			fwrite(&MapDataBace[0], sizeof(Map_ID)*MapDataBace.size(), 1, file);
			fclose(file);
		}
		if (onButton == IDNO)
		{
			int num = 1;
			while (1)
			{
				
				string number = to_string(num);
				string tmpFile = "data/" + worldname + number + ".map";
				if (stat(tmpFile.c_str(),&statBuf) != 0)
				{
				printfDx(tmpFile.c_str());
					fopen_s(&file, tmpFile.c_str(), "wb");
					fwrite(&expData, sizeof(expData), 1, file);
					fwrite(&MapDataBace[0], sizeof(Map_ID)*MapDataBace.size(), 1, file);
					fclose(file);
					break;
				}
				num++;
			}
		}

	}
	else
	{
		fopen_s(&file, WorldName.c_str(), "wb");
		fwrite(&expData, sizeof(expData), 1, file);
		fwrite(&MapDataBace[0], sizeof(Map_ID)*MapDataBace.size(), 1, file);
		fclose(file);
	}
	return true;
}

bool MapCtl::MapLoad(string worldname)
{
	string WorldName = "data/" + worldname + ".map";
	FILE *file;
	DataHeader expData;
	fopen_s(&file, WorldName.c_str(), "rb");
	fread(&expData, sizeof(expData), 1, file);
	MapDataBace.resize(expData.sizeX * expData.sizeY);
	fread(&MapDataBace[0], sizeof(Map_ID), MapDataBace.size(), file);
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
void MapCtl::SetDate(Date date)
{
	this->date = date;
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

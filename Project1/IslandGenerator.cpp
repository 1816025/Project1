#include <time.h>
#include "MapCtl.h"
#include "IslandGenerator.h"

void IslandGenerator::IslandMaker()
{
//	//“‡‚Ì—ÖŠs¶¬
//
	//“‡‚ÌÚ×ì¬
	auto IslandBase = [=](VECTOR2 pos,Map_ID id) 
	{
		for (int y = 0; y < DisplaySizeY; y++)
		{
			for (int x = 0; x < DisplaySizeX; x++)
			{
				if ((x % 60) > 5 && (y % 60) > 5 && (x % 60) < 55 && (y % 60) < 55)
				{
					lpMapCtl.SetMapData(VECTOR2(pos.x *x, pos.y *y), id);
				}
			}
		}
	};

	auto IslandParts = [=](Map_ID id,int range)
	{

		for (int cnt = 0; cnt <= 3; cnt++)
		{
			auto tmp_pos = VECTOR2(rand() % ((DisplaySizeX)), rand() % ((DisplaySizeY)));
			if ((tmp_pos.x / ChipSize) > 15 && (tmp_pos.y / ChipSize) > 15 && (tmp_pos.x / ChipSize) < 45 && (tmp_pos.y / ChipSize) < 45)
			{
				for (int num = 0; num < range; num++)
				{
						lpMapCtl.SetMapData(tmp_pos, id);
					
					switch ((rand() % 5))
					{
					case 1:
						tmp_pos.x += 10;
						break;
					case 2:
						tmp_pos.y += 10;
						break;
					case 3:
						tmp_pos.x -= 10;
						break;
					case 4:
						tmp_pos.y -= 10;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				cnt--;
				continue;
			}
		}

		for (int y = 0; y < DisplaySizeY; y++)
		{
			for (int x = 0; x < DisplaySizeX; x++)
			{
				if (lpMapCtl.GetMapData(VECTOR2(y, x)) == Map_ID::plain
					&& lpMapCtl.GetMapData(VECTOR2(y + 10, x)) == id
					&& lpMapCtl.GetMapData(VECTOR2(y - 10, x)) == id
					|| lpMapCtl.GetMapData(VECTOR2(y, x + 10)) == id
					&& lpMapCtl.GetMapData(VECTOR2(y, x - 10)) == id)
				{
					lpMapCtl.SetMapData(VECTOR2(y, x), id);
				}
				if (/*lpMapCtl.GetMapData(VECTOR2(y, x)) == Map_ID::water &&*/ ((x / ChipSize) <= 5 || (y / ChipSize) <= 5 || (x / ChipSize) >= 55 || (y / ChipSize) >= 55))
				{
					lpMapCtl.SetMapData(VECTOR2(y, x), Map_ID::water2);
				}
			}
		}
	};

	IslandBase(VECTOR2(ChipSize, ChipSize),Map_ID::plain);
	IslandParts(Map_ID::forest,2000);
	IslandParts(Map_ID::sand,500);
	IslandParts(Map_ID::rock,500);
	IslandParts(Map_ID::water,100);
}

void IslandGenerator::IslandInit()
{
	lpMapCtl.SetUp(VECTOR2(DisplaySizeX, DisplaySizeY), VECTOR2(ChipSize, ChipSize), VECTOR2(OffSetX, OffSetY));
}

IslandGenerator::IslandGenerator()
{
}

IslandGenerator::~IslandGenerator()
{
}

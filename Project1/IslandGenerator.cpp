#include <time.h>
#include "MapCtl.h"
#include "Noise.h" 
#include "IslandGenerator.h"

void IslandGenerator::IslandMaker()
{
////	//島の輪郭生成
////
//	//島の詳細作成
//	auto IslandBase = [=](VECTOR2 pos,Map_ID id) 
//	{
//		for (int y = 0; y < DisplaySizeY; y++)
//		{
//			for (int x = 0; x < DisplaySizeX; x++)
//			{
//				if ((x % 60) > 5 && (y % 60) > 5 && (x % 60) < 55 && (y % 60) < 55)
//				{
//					lpMapCtl.SetMapData(VECTOR2(pos.x *x, pos.y *y), id);
//				}
//			}
//		}
//	};
//
//	auto IslandParts = [=](Map_ID id,int range)
//	{
//
//		for (int cnt = 0; cnt <= 3; cnt++)
//		{
//			auto tmp_pos = VECTOR2(rand() % ((DisplaySizeX)), rand() % ((DisplaySizeY)));
//			if ((tmp_pos.x / ChipSize) > 15 && (tmp_pos.y / ChipSize) > 15 && (tmp_pos.x / ChipSize) < 45 && (tmp_pos.y / ChipSize) < 45)
//			{
//				for (int num = 0; num < range; num++)
//				{
//						lpMapCtl.SetMapData(tmp_pos, id);
//					
//					switch ((rand() % 5))
//					{
//					case 1:
//						tmp_pos.x += 10;
//						break;
//					case 2:
//						tmp_pos.y += 10;
//						break;
//					case 3:
//						tmp_pos.x -= 10;
//						break;
//					case 4:
//						tmp_pos.y -= 10;
//						break;
//					default:
//						break;
//					}
//				}
//			}
//			else
//			{
//				cnt--;
//				continue;
//			}
//		}
//
//		for (int y = 0; y < DisplaySizeY; y++)
//		{
//			for (int x = 0; x < DisplaySizeX; x++)
//			{
//				if (lpMapCtl.GetMapData(VECTOR2(y, x)) == Map_ID::plain
//					&& lpMapCtl.GetMapData(VECTOR2(y + 10, x)) == id
//					&& lpMapCtl.GetMapData(VECTOR2(y - 10, x)) == id
//					|| lpMapCtl.GetMapData(VECTOR2(y, x + 10)) == id
//					&& lpMapCtl.GetMapData(VECTOR2(y, x - 10)) == id)
//				{
//					lpMapCtl.SetMapData(VECTOR2(y, x), id);
//				}
//				if (((x / ChipSize) <= 5 || (y / ChipSize) <= 5 || (x / ChipSize) >= 55 || (y / ChipSize) >= 55))
//				{
//					lpMapCtl.SetMapData(VECTOR2(y, x), Map_ID::water2);
//				}
//			}
//		}
//	};
//
//	IslandBase(VECTOR2(ChipSize, ChipSize),Map_ID::plain);
//	IslandParts(Map_ID::forest,2000);
//	IslandParts(Map_ID::sand,500);
//	IslandParts(Map_ID::rock,500);
//	IslandParts(Map_ID::water,100);
	Map_ID id = Map_ID::water2;
	for (int i = 0; i < DisplaySizeY; i++)
	{
		for (int j = 0; j < DisplaySizeX; j++)
		{
			float x = (float)j /*(rand() % 2 + 1)*/;
			float y = (float)i /*(rand()%2 + 1)*/;
			const int tmp_id = fabsf(floorf((float)255 * (lpNoise.ValueNoise(x, y) + 0.5)));

			if (j  > 2 && i> 2 && j < 57 && i< 57)
			{
				if (tmp_id < 20)
				{
					id = Map_ID::water;
					if (tmp_id < 10)
					{
						id = Map_ID::water2;
					}
				}
				else if (tmp_id >= 20)
				{
					id = Map_ID::plain;
					if (tmp_id > 90)
					{
						id = Map_ID::rock;
					}
				}
				if (id < Map_ID::water)
				{
					id = Map_ID::water2;
				}
				lpMapCtl.SetMapData(VECTOR2(ChipSize *j, ChipSize *i), id);
			}
			//lpMapCtl.SetMapData(VECTOR2(ChipSize *j, ChipSize *i), id);
		}
	}
}

void IslandGenerator::IslandInit(void)
{
	lpMapCtl.SetUp(VECTOR2(DisplaySizeX, DisplaySizeY), VECTOR2(ChipSize, ChipSize), VECTOR2(OffSetX, OffSetY));
}

IslandGenerator::IslandGenerator()
{
}

IslandGenerator::~IslandGenerator()
{
}

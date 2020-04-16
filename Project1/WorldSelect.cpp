#include "DxLib.h"
#include "ImageMng.h"
#include "BaseScene.h"
#include "Game.h"
#include "WorldSelect.h"

WorldSelect::WorldSelect()
{
}

WorldSelect::~WorldSelect()
{
}

unique_base WorldSelect::UpDate(unique_base own, const KeyCtl & controller)
{
	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;

	for (int cnt = 0; cnt < WorldData.size(); cnt++)
	{
		if (Click&(ClickOld) && Mpos > VECTOR2(10 + 140 * cnt, ScreenSize.y / 2) && Mpos < VECTOR2(150 + 140 * cnt, ScreenSize.y / 2 + 120))
		{
			return std::make_unique<Game>(WorldData[cnt]);
		}
	}
	Draw();
	return move(own);
}

void WorldSelect::Draw()
{
	int roopcnt = 0;
	FindHandle = FileRead_findFirst("img/worldimg/New World*.png", &FileInfo);
	if (FindHandle != (DWORD_PTR)-1)
	{
		do {
			WorldName = FileInfo.Name;
			WorldData.resize(1 + roopcnt);
			WorldData[0 + roopcnt] = WorldName;
			roopcnt++;
		} while (FileRead_findNext(FindHandle, &FileInfo) == 0);
	}
	ClsDrawScreen();
	for (int cnt = 0; cnt < WorldData.size(); cnt++)
	{
		DrawFormatString(10 + 140 * cnt, ScreenSize.y / 2 - 30, 0xffffff, "%s", WorldData[cnt].c_str());
		DrawRotaGraph2(10+140 * cnt, ScreenSize.y/2, 0, 0, 0.2, 0, IMAGE_ID("img/worldimg/" + WorldData[cnt])[0], false, false);
		DrawBox(10 + 140 * cnt, ScreenSize.y / 2 , 130 + 140 * cnt, ScreenSize.y / 2 + 120, 0xff00, false);
	}
	ScreenFlip();
}

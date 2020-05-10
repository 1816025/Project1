#include "DxLib.h"
#include "ImageMng.h"
#include "BaseScene.h"
#include "Game.h"
#include "WorldSelect.h"

WorldSelect::WorldSelect()
{
	drawOffset = { 0,0 };
}

WorldSelect::~WorldSelect()
{
}

unique_base WorldSelect::UpDate(unique_base own, const KeyCtl & controller)
{
	Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;
	drawOffset.y -= (controller.CheckWheel()%2)*10;
	Mpos = Mpos ;
	for (int cnt = 0; cnt < WorldData.size(); cnt++)
	{
		if (Click&(ClickOld) && (Mpos ) > VECTOR2(10 , ScreenSize.y / 2 + 140 * cnt+ drawOffset.y) && (Mpos ) < VECTOR2(150 , ScreenSize.y / 2 + 120+ 140 * cnt + drawOffset.y))
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
		DrawFormatString(0 ,0, 0xffffff, "%d", drawOffset.y);
		DrawFormatString(0 ,20, 0xffffff, "%d", Mpos.y);
		DrawFormatString(140 , ScreenSize.y / 2 + drawOffset.y+ 140 * cnt, 0xffffff, "%s", WorldData[cnt].c_str());
		DrawRotaGraph2(10, ScreenSize.y/2 + drawOffset.y+140 * cnt, 0, 0, 0.2, 0, IMAGE_ID("img/worldimg/" + WorldData[cnt])[0], false, false);
		DrawBox(10 , ScreenSize.y / 2 + drawOffset.y+ 140 * cnt, 130 , ScreenSize.y / 2 +120+ drawOffset.y + 140 * cnt, 0xff00, false);
	}
	ScreenFlip();
}

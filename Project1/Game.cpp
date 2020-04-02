#include <time.h>
#include "DxLib.h"
#include "KeyCtl.h"
#include "BaseScene.h"
#include "MapCtl.h"
#include "IslandGenerator.h"
#include "Game.h"

Game::Game()
{
	Init();
}

Game::~Game()
{
}

int Game::Init()
{
	lpIslandGenerator.IslandInit();
	date = { 1,1,1,0,0 };
	Frame = 0;
	TimeTransFlag = true; //trueでFrame加算
	Debug = false;
	srand(time(NULL));
	return 0;
}

void Game::Timer(const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);

	//ｹﾞｰﾑ内時間とﾌﾚｰﾑの加算
	if (TimeTransFlag)
	{
		Frame++;
		date.minute = (Frame % 60);
		if (date.minute % 60 == 0)
		{
			date.hour += 1;
			if (date.hour % 24 == 0)
			{
				date.day += 1;
				date.hour = 0;
				if (date.day % 30 == 0)
				{
					date.month += 1;
					date.day = 1;
					if (date.month % 12 == 0)
					{
						date.year += 1;
						date.month = 1;
					}
				}
			}
		}
	}


	if (Key[KEY_INPUT_TAB] & ~KeyOld[KEY_INPUT_TAB])
	{
		switch (TimeTransFlag)
		{
		case true:
			TimeTransFlag = false;
			break;
		case false:
			TimeTransFlag = true;
			break;
		}
	}

	if (Key[KEY_INPUT_F3] & ~KeyOld[KEY_INPUT_F3])
	{
		switch (Debug)
		{
		case true:
			Debug = false;
			break;
		case false:
			Debug = true;
			break;
		}
	}

}

void Game::Draw()
{
	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x,&Mpos.y);
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	if (Debug)
	{
		DrawFormatString(600, 0, 0xffffff, "%d", Frame);
	}

	lpMapCtl.Draw();
	DrawFormatString(0, 0, 0xffffff, "%d年目 %2d月%2d日\n%2d時%2d分", date.year, date.month, date.day, date.hour, date.minute);
	for (int y = 0; y <= DisplaySizeY / ChipSize; y++)
	{
		DrawLine(100,  50+(ChipSize*y), 100+ (ChipSize * (DisplaySizeY / ChipSize)), 50+(ChipSize*y), 0x666666);
	}
	for (int x = 0; x <= DisplaySizeX / ChipSize; x++)
	{
		DrawLine(100+(ChipSize*x), 50,100+ (ChipSize*x), 50+(ChipSize*(DisplaySizeX / ChipSize)),  0x666666);
	}

	DrawFormatString(0, 680, 0xffffff, "Mpos.x%d Mpos.y%d",Mpos.x,Mpos.y);
	DrawFormatString(0, 700, 0xffffff, "type: %d",lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x -100,Mpos.y-50)).color);
	DrawFormatString(0, 720, 0xffffff, "color: %x", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).color);
	DrawFormatString(0, 740, 0xffffff, "Lv: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 60)).Lv);
	DrawFormatString(0, 760, 0xffffff, "ProductionSpeed: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).ProductionSpeed);
	DrawFormatString(0, 780, 0xffffff, "Nature: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).Nature);

	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
}

unique_base Game::UpDate(unique_base own,const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);

	Timer(controller);
	Draw();

	if (Key[KEY_INPUT_D] & ~KeyOld[KEY_INPUT_D])
	{
		lpIslandGenerator.IslandInit();
	}

	if (Key[KEY_INPUT_S] & ~KeyOld[KEY_INPUT_S])
	{
		lpIslandGenerator.IslandMaker();
	}
	return move(own);
}

const Date Game::Getdate()
{
	return date;
}

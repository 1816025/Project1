#include "DxLib.h"
#include "KeyCtl.h"
#include "BaseScene.h"
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
	Frame = 0;
	TimeTransFlag = true; //trueでFrame加算
	return 0;
}

void Game::Draw()
{
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "%d", Frame);
	DrawFormatString(0, 50, 0xffffff, "%d", TimeTransFlag);
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
}

unique_base Game::UpDate(unique_base own,const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);
	if (Key[KEY_INPUT_TAB]&~KeyOld[KEY_INPUT_TAB])
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
	if (TimeTransFlag)
	{
		Frame++;
	}
	Draw();
	return move(own);
}

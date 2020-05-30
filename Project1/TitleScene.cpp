#include "DxLib.h"
#include "ImageMng.h"
#include "KeyCtl.h"
#include "SceneMng.h"
#include "WorldSelect.h"
#include "Game.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

unique_base TitleScene::UpDate(unique_base own, const KeyCtl & controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;
	VECTOR2 Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	if ((Click&(~ClickOld)) && (Mpos > start.NewWorld&&Mpos < start.NewWorld + VECTOR2{ 400,80 }))
	{
		return std::make_unique<Game>();
	}
	
	if ((Click&(~ClickOld)) && (Mpos > start.Continue&&Mpos < start.Continue + VECTOR2{ 400,80 }))
	{
		return std::make_unique<WorldSelect>();
	}
	if (Key[KEY_INPUT_ESCAPE] & ~KeyOld[KEY_INPUT_ESCAPE])
	{
		lpSceneMng.SetEndFlag(true);
	}
	TitleDraw();
	return move(own);
}

void TitleScene::Init()
{
	start.NewWorld = { (ScreenSize.x / 2) - (400 / 2),(ScreenSize.y)-240 };
	start.Continue = { (ScreenSize.x / 2) - (400 / 2),(ScreenSize.y) - 120 };
}

void TitleScene::TitleDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0,lpImageMng.GetID("img/books.png")[0],false);
	DrawGraph(start.NewWorld.x,start.NewWorld.y,lpImageMng.GetID("img/New start.png", VECTOR2(400, 80), VECTOR2(1, 2))[1],false);
	DrawGraph(start.Continue.x, start.Continue.y,lpImageMng.GetID("img/ReStart.png", VECTOR2(400, 80), VECTOR2(1, 2))[1],false);
	ScreenFlip();
}

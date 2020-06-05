#include "DxLib.h"
#include "ImageMng.h"
#include "SoundMng.h"
#include "KeyCtl.h"
#include "SceneMng.h"
#include "WorldSelect.h"
#include "Game.h"
#include "VECTOR2.h"
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
	auto Click = controller.GetClick(NOW);
	auto ClickOld = controller.GetClick(OLD);
	VECTOR2 Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	if ((Click&(~ClickOld)) && (Mpos > start.NewWorld&&Mpos < start.NewWorld + VECTOR2{ 400,80 }))
	{
		lpSoundMng.PlaySound("sounddata/PaperTake.mp3", PlayType::Normal);
		return std::make_unique<Game>();
	}

	if ((Click&(~ClickOld)) && (Mpos > start.Continue&&Mpos < start.Continue + VECTOR2{ 400,80 }))
	{
		lpSoundMng.PlaySound("sounddata/PaperTake.mp3", PlayType::Normal);
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
	GetGraphSize(lpImageMng.GetID("img/titleimg.png")[0], &titleSize.x, &titleSize.y);
	lpSoundMng.GetID("sounddata/PaperTake.mp3");
}

void TitleScene::TitleDraw(void)
{
	ClsDrawScreen();
	
	DrawGraph(0, 0,lpImageMng.GetID("img/books.png")[0],false);
	DrawGraph((ScreenSize.x / 2) - titleSize.x/2, (ScreenSize.y / 2) - titleSize.y/1.22,lpImageMng.GetID("img/titleimg.png")[0],true);
	DrawGraph((ScreenSize.x / 2) - titleSize.x / 2 + 50, 70,lpImageMng.GetID("img/TitleLogo.png")[0],true);
	DrawGraph(start.NewWorld.x,start.NewWorld.y,lpImageMng.GetID("img/New start.png", VECTOR2(400, 80), VECTOR2(1, 2))[1],false);
	DrawGraph(start.Continue.x, start.Continue.y,lpImageMng.GetID("img/ReStart.png", VECTOR2(400, 80), VECTOR2(1, 2))[1],false);
	ScreenFlip();
}

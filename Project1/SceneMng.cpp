#include "DxLib.h"
#include "KeyCtl.h"
#include "MapCtl.h"
#include "TitleScene.h"
#include "Game.h"
#include "SceneMng.h"

void SceneMng::Run(void)
{
	activeScene = std::make_unique<TitleScene>();
	// ゲームループ.
	while (ProcessMessage() == 0 && endflag == false)
	{
		keyCtl->UpDate();
		activeScene = activeScene->UpDate(move(activeScene), *keyCtl);
	}
}

void SceneMng::SetEndFlag(bool flag)
{
	endflag = flag;
}

SceneMng::SceneMng()
{
	SysInit();
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit()
{
	// 画面モードの設定
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(TRUE);			// ウインドウモードに.

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	endflag = false;
	keyCtl = std::make_unique<KeyCtl>();
	return true;
}

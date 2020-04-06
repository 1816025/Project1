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
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCtl->UpDate();
		activeScene = activeScene->UpDate(move(activeScene), *keyCtl);
	}
	int onButton = MessageBox(NULL, "YES: 保存して終了 NO: 保存せずに終了", "上書きして終了しますがよろしいですか？", MB_YESNO);
	if (onButton == IDYES)
	{
		lpMapCtl.MapSave(false, lpMapCtl.GetWorldName());
	}
	if (onButton == IDNO)
	{
	}
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
	SetGraphMode(800, 800, 16);
	ChangeWindowMode(TRUE);			// ウインドウモードに.

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	keyCtl = std::make_unique<KeyCtl>();
	return true;
}

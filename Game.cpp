#include "DxLib.h"
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
	// 画面モードの設定
	SetGraphMode(640, 480, 16);	
	ChangeWindowMode(TRUE);			// ウインドウモードに.

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

void Game::Draw()
{
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
}

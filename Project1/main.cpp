//-----------------------------------------------------------------------------
// @brief  メイン処理.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Game.h"

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	Game *game = new Game();
	// ゲームループ.
	while (ProcessMessage()==0 && CheckHitKey(KEY_INPUT_ESCAPE)== 0)
	{
		//描画
		game->Draw();
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
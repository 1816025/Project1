#include "KeyCtl.h"
#include "DxLib.h"

bool KeyCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// 全てのキーの入力状態を得る


	Click.old = Click.now;
	Click.now = (GetMouseInput()&MOUSE_INPUT_LEFT);			//クリック情報の取得

	wheel = GetMouseWheelRotVol() % 2;	//ﾎｲｰﾙ情報の取得

	return true;
}

const KeyArray & KeyCtl::GetCtl(KEY_TYPE type) const
{
	if (type == OLD)
	{
		return dataOld;
	}
	return data;
}

const bool& KeyCtl::GetClick(KEY_TYPE type) const
{
	if (type == OLD)
	{
		return Click.old;
	}
	return Click.now ;
}

const int &KeyCtl::CheckWheel()const
{
	return wheel;
}

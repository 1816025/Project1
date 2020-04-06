#include "KeyCtl.h"
#include "DxLib.h"

bool KeyCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// 全てのキーの入力状態を得る


	Click.old = Click.now;
	Click.now = GetMouseInput();			//クリック情報の取得

	wheel.old = wheel.now;
	wheel.now = GetMouseWheelRotVol() % 2;	//ﾎｲｰﾙ情報の取得

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

const bool KeyCtl::GetClick(int mousetype, KEY_TYPE type)
{
	if (type == OLD)
	{
		return Click.old;
	}
	return Click.now & mousetype;
}

const bool KeyCtl::CheckWheel(KEY_TYPE type)
{
	if (type == OLD)
	{
		return wheel.old;
	}
	return wheel.now & type;
}

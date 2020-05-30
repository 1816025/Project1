#include "KeyCtl.h"
#include "DxLib.h"

bool KeyCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// �S�ẴL�[�̓��͏�Ԃ𓾂�


	Click.old = Click.now;
	Click.now = (GetMouseInput()&MOUSE_INPUT_LEFT);			//�N���b�N���̎擾

	wheel = GetMouseWheelRotVol() % 2;	//β�ُ��̎擾

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

#include "KeyCtl.h"
#include "DxLib.h"

bool KeyCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// �S�ẴL�[�̓��͏�Ԃ𓾂�


	Click.old = Click.now;
	Click.now = GetMouseInput();			//�N���b�N���̎擾

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

const bool& KeyCtl::GetClick(int mousetype, KEY_TYPE type)
{
	if (GetMouseInput() == MOUSE_INPUT_LEFT)
	{
		if (!Click.now)
		{
			Click.now = true;

		}
	}
	else
	{
		Click.now = false;
	}
	return Click.now ;
}

const int &KeyCtl::CheckWheel()const
{
	return wheel;
}

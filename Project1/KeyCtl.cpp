#include "KeyCtl.h"
#include "DxLib.h"

bool KeyCtl::UpDate(void)
{
	dataOld = data;
	GetHitKeyStateAll(&data[0]);		// �S�ẴL�[�̓��͏�Ԃ𓾂�

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

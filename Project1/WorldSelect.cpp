#include "DxLib.h"
#include "WorldSelect.h"

WorldSelect::WorldSelect()
{
}

WorldSelect::~WorldSelect()
{
}

unique_base WorldSelect::UpDate(unique_base own, const KeyCtl & controller)
{
	return move(own);
}

string WorldSelect::WorldChoice()
{
	return worldName;
}

void WorldSelect::Draw()
{
	ClsDrawScreen();
	ScreenFlip();
}

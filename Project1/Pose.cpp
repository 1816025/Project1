#include "DxLib.h"
#include "BaseScene.h"
#include "imageMng.h"
#include "Pose.h"
Pose::Pose()
{

}
void Pose::Draw(bool Optionflag)
{
	DrawGraph(0, 0, lpImageMng.GetID("img/bgfilter.png")[0], true);
	DrawFormatString(700, ScreenSize.y - 30, 0xffffff, "Now Pose...");
	if (Optionflag == true)
	{

	}
}

Pose::~Pose()
{
}

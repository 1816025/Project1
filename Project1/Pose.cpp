#include "DxLib.h"
#include "BaseScene.h"
#include "imageMng.h"
#include "Pose.h"
Pose::Pose()
{

}
void Pose::Draw(void)
{
	DrawGraph(0, 0, lpImageMng.GetID("img/bgfilter.png")[0], true);
	DrawGraph(100, DisplaySizeY / 2, lpImageMng.GetID("img/bar.png")[0], true);
}

Pose::~Pose()
{
}

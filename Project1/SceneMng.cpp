#include "DxLib.h"
#include "KeyCtl.h"
#include "MapCtl.h"
#include "TitleScene.h"
#include "Game.h"
#include "SceneMng.h"

void SceneMng::Run(void)
{
	activeScene = std::make_unique<TitleScene>();
	// �Q�[�����[�v.
	while (ProcessMessage() == 0 && endflag == false)
	{
		keyCtl->UpDate();
		activeScene = activeScene->UpDate(move(activeScene), *keyCtl);
	}
}

void SceneMng::SetEndFlag(bool flag)
{
	endflag = flag;
}

SceneMng::SceneMng()
{
	SysInit();
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit()
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(TRUE);			// �E�C���h�E���[�h��.

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	endflag = false;
	keyCtl = std::make_unique<KeyCtl>();
	return true;
}

#include "DxLib.h"
#include "KeyCtl.h"
#include "Game.h"
#include "SceneMng.h"

void SceneMng::Run(void)
{
	activeScene = std::make_unique<Game>();
	// �Q�[�����[�v.
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCtl->UpDate();
		activeScene = activeScene->UpDate(move(activeScene), *keyCtl);
	}
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
	SetGraphMode(800, 800, 16);
	ChangeWindowMode(TRUE);			// �E�C���h�E���[�h��.

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;
	}

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	keyCtl = std::make_unique<KeyCtl>();
	return true;
}

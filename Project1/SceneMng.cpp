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
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCtl->UpDate();
		activeScene = activeScene->UpDate(move(activeScene), *keyCtl);
	}
	int onButton = MessageBox(NULL, "YES: �ۑ����ďI�� NO: �ۑ������ɏI��", "�㏑�����ďI�����܂�����낵���ł����H", MB_YESNO);
	if (onButton == IDYES)
	{
		lpMapCtl.MapSave(false, lpMapCtl.GetWorldName());
	}
	if (onButton == IDNO)
	{
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

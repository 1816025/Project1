#include "DxLib.h"
#include "Game.h"

Game::Game()
{
	Init();
}

Game::~Game()
{
}

int Game::Init()
{
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(640, 480, 16);	
	ChangeWindowMode(TRUE);			// �E�C���h�E���[�h��.

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	return 0;
}

void Game::Draw()
{
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
	ScreenFlip();
}

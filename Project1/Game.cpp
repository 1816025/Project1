#include "DxLib.h"
#include "KeyCtl.h"
#include "BaseScene.h"
#include "MapCtl.h"
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
	lpMapCtl.SetUp(VECTOR2(DisplaySizeX, DisplaySizeY), VECTOR2(ChipSize, ChipSize), VECTOR2(100, 50));
	date = { 1,1,1,0,0 };
	Frame = 0;
	TimeTransFlag = true; //true��Frame���Z
	Debug = false;
	return 0;
}

void Game::Timer(const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);

	//�ްѓ����Ԃ��ڰт̉��Z
	if (TimeTransFlag)
	{
		Frame++;
		date.minute = (Frame % 60);
		if (date.minute % 60 == 0)
		{
			date.hour += 1;
			if (date.hour % 24 == 0)
			{
				date.day += 1;
				date.hour = 0;
				if (date.day % 30 == 0)
				{
					date.month += 1;
					date.day = 1;
					if (date.month % 12 == 0)
					{
						date.year += 1;
						date.month = 1;
					}
				}
			}
		}
	}


	if (Key[KEY_INPUT_TAB] & ~KeyOld[KEY_INPUT_TAB])
	{
		switch (TimeTransFlag)
		{
		case true:
			TimeTransFlag = false;
			break;
		case false:
			TimeTransFlag = true;
			break;
		}
	}

	if (Key[KEY_INPUT_F3] & ~KeyOld[KEY_INPUT_F3])
	{
		switch (Debug)
		{
		case true:
			Debug = false;
			break;
		case false:
			Debug = true;
			break;
		}
	}

	if (Key[KEY_INPUT_S] & ~KeyOld[KEY_INPUT_S])
	{
		for (int y = 0; y < DisplaySizeY / ChipSize; y++)
		{
			for (int x = 0; x < DisplaySizeX / ChipSize; x++)
			{
				if((x%60) > 15 && (y%60)>15 && (x % 60) < 45 && (y % 60) <45 )
				lpMapCtl.SetMapData(VECTOR2(ChipSize * x, ChipSize * y), Map_ID::sand);
			}

		}
	}

}

void Game::Draw()
{
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	if (Debug)
	{
		DrawFormatString(600, 0, 0xffffff, "%d", Frame);
	}

	lpMapCtl.Draw();
	DrawFormatString(0, 0, 0xffffff, "%d�N�� %2d��%2d��\n%2d��%2d��", date.year, date.month, date.day, date.hour, date.minute);
	for (int y = 0; y <= DisplaySizeY / ChipSize; y++)
	{
		DrawLine(100,  50+(ChipSize*y), 100+ (ChipSize * (DisplaySizeY / ChipSize)), 50+(ChipSize*y), 0x666666);
	}
	for (int x = 0; x <= DisplaySizeX / ChipSize; x++)
	{
		DrawLine(100+(ChipSize*x), 50,100+ (ChipSize*x), 50+(ChipSize*(DisplaySizeX / ChipSize)),  0x666666);
	}

	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
	ScreenFlip();
}

unique_base Game::UpDate(unique_base own,const KeyCtl &controller)
{
	Timer(controller);
	Draw();
	return move(own);
}

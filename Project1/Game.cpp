#include <string>
#include <time.h>
#include <Windows.h>

#include "DxLib.h"

#include "BaseScene.h"
#include "SceneMng.h"
#include "Pose.h"

#include "KeyCtl.h"				//�ǂ̷��������ꂽ����m��

#include "ImageMng.h"			//�摜�̓ǂݍ���
#include "SoundMng.h"			//Sound�̓ǂݍ��݁A�Đ�
#include "BookList.h"

#include "Noise.h"				//�m�C�Y�𐶐�����
#include "MAP_ID.h"
#include "MapCtl.h"				//�}�b�v�̑���
#include "Event.h"				//�C�x���g

#include "Game.h"				//����

Game::Game()
{
	Init();
	lpNoise.SetHash(rand());
	struct stat statBuf;
	int num = 1;
	if (stat("data/New World.map", &statBuf) == 0)
	{
		while (1)
		{
			WorldName = "New World";
			string number = to_string(num);

			WorldName = WorldName + number;

			string tmpFile = "data/" + WorldName + ".map";
			if (stat(tmpFile.c_str(), &statBuf) != 0)
			{
				lpMapCtl.MapSave(true, WorldName);
				break;
			}
			num++;
		}
	}
	else
	{
		lpMapCtl.MapSave(true, "New World");
		WorldName = "New World";
	}
}
Game::Game(string WorldName)
{
	Init();
	lpMapCtl.MapLoad(WorldName);
	this->WorldName = WorldName;
}

Game::~Game()
{
}

int Game::Init()
{
	date = {DayCycle::Day,1,1,1,0,0 };
	Frame = 0;
	TimeTransFlag = true; //true��Frame���Z
	SetObjectFlag = false;
	CntSpeed = 1;
	Debug = false;
	srand(time(NULL));
	auto ImageSize = [=](string name,VECTOR2 divSize,VECTOR2 divCnt)
	{
		GetGraphSize(lpImageMng.GetID("img/" + name + ".png", divSize, divCnt)[1], &this->ImageSize[name].x,&this->ImageSize[name].y);
	};
	ImageSize("icon", VECTOR2(30, 30), VECTOR2(3, 1));
	ImageSize("TAB", VECTOR2(150, 70), VECTOR2(2, 1));
	id = Map_ID::BOOK_SHELF;
	lpMapCtl.SetUp(VECTOR2(400, 400), VECTOR2(16, 16), VECTOR2(300, 100));
	//lpSoundMng.GetID("sounddata/wave.mp3");
	//lpSoundMng.PlaySound("sounddata/wave.mp3", PlayType::Loop);
	lpBookList.GetInstance();
	return 0;
}

void Game::Timer(const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;

	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);

	//�ްѓ����Ԃ��ڰт̉��Z
	Frame++;

	date.daycycle = static_cast<DayCycle>(date.hour / 24 % static_cast<int>(DayCycle::Max));
	OpenFlag = (date.day % 4 != 0 ? true : false);
	if (Frame%(60) == 0)
	{
		date.minute += 1;
		if (date.minute % (60) == 0)
		{
			date.hour += 1;
			date.minute = 0;
			if (date.hour >= 12)
			{
				date.daycycle = DayCycle::Night;
			}
			else
			{
				date.daycycle = DayCycle::Day;
			}
			if (date.day > 24)
			{
				date.month += 1;
				date.hour = 0;
				if (date.month > 12)
				{
					date.year += 1;
					date.month = 1;
				}
			}
		}
	}
}

unique_base Game::UpDate(unique_base own,const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;


	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	if (TimeTransFlag)
	{
		Timer(controller);
	}
	lpMapCtl.SetDate(date);

	//�ݒu����ID�̐؂�ւ�
	if (Key[KEY_INPUT_LCONTROL] & (~KeyOld[KEY_INPUT_LCONTROL]))
	{
		id = (Map_ID)(id + 1);
		if (id >= Map_ID::CHAIR)
		{
			id = Map_ID::BOOK_SHELF;
		}
	}

	//�{�݂̐ݒu
	if (Click&(ClickOld)&& SetObjectFlag == true)
	{
		lpMapCtl.SetMapData(Mpos + VECTOR2(-OffSetX, -OffSetY), id);
	}

	for (int num = 0; num < 2; num++)
	{
		if (Click&(ClickOld) && Mpos > VECTOR2(15 + (15 * num + ImageSize["TAB"].x*num), ScreenSize.y - ImageSize["TAB"].y) && Mpos < VECTOR2(ImageSize["TAB"].x + 15 + (15 * num + ImageSize["TAB"].x*num), ScreenSize.y))
		{
			switch (num)
			{
			case 0:
				break;
			case 1:
				TimeTransFlag = false;
				break;
			default:
				break;
			}
		}
	}

	if (Key[KEY_INPUT_ESCAPE] & ~KeyOld[KEY_INPUT_ESCAPE])
	{
		lpSceneMng.SetEndFlag(true);
		lpBookList.DataSave("BookArchive");
		lpMapCtl.MapSave(false, WorldName);
	}if (Key[KEY_INPUT_A] & ~KeyOld[KEY_INPUT_A])
	{
		lpBookList.DataLoad("BookArchive");
		lpMapCtl.MapLoad("New World.map");
	}
	if (date.daycycle == DayCycle::Day)
	{
		if (lpEvent.CheckEvent())
		{
			TimeTransFlag = false;
		}

		if (Key[KEY_INPUT_S] & ~KeyOld[KEY_INPUT_S])
		{
			lpEvent.PlayEvent(EVENT::Donation);
		}

		if (Key[KEY_INPUT_W] & ~KeyOld[KEY_INPUT_W])
		{
			lpEvent.PlayEvent(EVENT::Debut);
		}

		if (lpEvent.GetEvent().id == EVENT::Raid && lpEvent.GetEvent().flag == true)
		{
			lpEvent.SetEvent(false, EVENT::Raid);
		}
	}
	else
	{

	}
	if (lpEvent.CheckEvent() == true)
	{
		lpEvent.UpDate(controller);
	}
	Phase(date.daycycle);
	Draw();
	return move(own);
}

void Game::Draw()
{
	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	// ��ʂ�������(�^�����ɂ���)
	ClearDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("img/books.png")[0], false);
	if (Debug)
	{
		DrawFormatString(600, 0, 0xffffff, "%d", Frame);
	}

	if (lpEvent.CheckEvent() == true)
	{
		lpEvent.Draw();
	}
	else
	{
		lpMapCtl.Draw();
		for (int y = 0; y <= DisplaySizeY / ChipSize; y++)
		{
			DrawLine(OffSetX, OffSetY + (ChipSize*y), OffSetX + (ChipSize * (DisplaySizeY / ChipSize)), OffSetY + (ChipSize*y), 0x666666);
		}
		for (int x = 0; x <= DisplaySizeX / ChipSize; x++)
		{
			DrawLine(OffSetX + (ChipSize*x), OffSetY, OffSetX + (ChipSize*x), OffSetY + (ChipSize*(DisplaySizeX / ChipSize)), 0x666666);
		}
	}
	//DrawFormatString(0, 0, 0xffffff, "%d�N�� %2d��%2d��\n%2d��%2d��", date.year, date.month, date.day, date.hour, date.minute);
	for (int num = 0; num < (int)BookTitle::Max; num++)
	{
		DrawFormatString(0, 30 * num, 0xffffff, "%d", lpBookList.GetLibrary()[num]);
	}
	DrawFormatString(0, 680, 0xffffff, "Mpos.x%d Mpos.y%d", Mpos.x, Mpos.y);
	DrawFormatString(80, 0, 0xffffff, "ID:%d", static_cast<int>(sizeof(Date)));
	DrawFormatString(0, 760, 0xffffff, "Nature: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).BuildFlag);
	// ����ʂ̓��e��\��ʂɃR�s�[����i�`��̊m��j.
	ScreenFlip();
}

void Game::Phase(DayCycle cycle)
{
	switch (cycle)
	{
	case DayCycle::Day:
		if (OpenFlag == true)
		{
			SetObjectFlag = false;/*
			if(rand()%30==0)
			{
				lpEvent.PlayEvent(EVENT::Donation);
			}if(rand()%10==0)
			{
				lpEvent.PlayEvent(EVENT::Debut);
			}*/
		}
		else
		{
			SetObjectFlag = true;
		}
		break;
	case DayCycle::Night:
		if (rand() % 40 == 0)
		{

		}
		if (rand() % 60 == 0)
		{
			//�F�D�x�㏸�C�x���g
		}
		break;
	default:
		break;
	}
}

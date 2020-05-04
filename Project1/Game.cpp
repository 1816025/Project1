#include <string>
#include <time.h>
#include "DxLib.h"
#include "KeyCtl.h"
#include "ImageMng.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "Noise.h"
#include "IslandGenerator.h"
#include "Factory.h"
#include "MAP_ID.h"
#include "MapCtl.h"
#include "Research.h"
#include "Game.h"

Game::Game()
{
	Init();
	lpNoise.SetHash(rand());
	lpIslandGenerator.IslandMaker();
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
	lpIslandGenerator.IslandInit();
	date = { 1,1,1,0,0 };
	Frame = 0;
	TimeTransFlag = true; //trueでFrame加算
	CntSpeed = 1;
	Debug = false;
	srand(time(NULL));
	auto IconSize = [=](string name)
	{
		GetGraphSize(lpImageMng.GetID("img/icon.png", VECTOR2(30, 30), VECTOR2(3, 1))[1], &this->IconSize[name].x,&this->IconSize[name].y);
	};
	IconSize("stop");
	IconSize("play");
	IconSize("fastplay");
	id = Map_ID::mine;
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

	//ｹﾞｰﾑ内時間とﾌﾚｰﾑの加算
	if (TimeTransFlag)
	{
		Frame += CntSpeed;
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

	for (int num = 0; num < IconSize.size(); num++)
	{
		if (Click&(ClickOld) && Mpos > VECTOR2(300 + IconSize["stop"].x * num, 0) && Mpos < VECTOR2(300 + IconSize["stop"].x * num + IconSize["stop"].x, IconSize["stop"].y))
		{
			switch (num)
			{
			case 0:
				TimeTransFlag = false;
				break;
			case 1:
				TimeTransFlag = true;
				CntSpeed = 1;
				break;
			case 2:
				TimeTransFlag = true;
				CntSpeed = 2;
				break;
			}
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

}

void Game::Draw()
{
	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x,&Mpos.y);
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	if (Debug)
	{
		DrawFormatString(600, 0, 0xffffff, "%d", Frame);
	}

	lpMapCtl.Draw();
	DrawFormatString(0, 0, 0xffffff, "%d年目 %2d月%2d日\n%2d時%2d分", date.year, date.month, date.day, date.hour, date.minute);
	for (int y = 0; y <= DisplaySizeY / ChipSize; y++)
	{
		DrawLine(100,  50+(ChipSize*y), 100+ (ChipSize * (DisplaySizeY / ChipSize)), 50+(ChipSize*y), 0x666666);
	}
	for (int x = 0; x <= DisplaySizeX / ChipSize; x++)
	{
		DrawLine(100+(ChipSize*x), 50,100+ (ChipSize*x), 50+(ChipSize*(DisplaySizeX / ChipSize)),  0x666666);
	}

	auto Draw = [=](string path,int num)
	{
		DrawGraph(300 + (IconSize[path].x * num), 0, lpImageMng.GetID("img/icon.png", VECTOR2(30, 30), VECTOR2(3, 1))[num], true);
	};

	Draw("stop",0);
	Draw("play",1);
	Draw("fastplay",2);

	DrawFormatString(0, 680, 0xffffff, "Mpos.x%d Mpos.y%d",Mpos.x,Mpos.y);
	DrawFormatString(0, 700, 0xffffff, "ID:%d",static_cast<int>(id));
	DrawFormatString(0, 720, 0xffffff, "type: %d",lpMapCtl.GetPanelConter(Map_ID::field));
	DrawFormatString(0, 760, 0xffffff, "Nature: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).BuildFlag);
	lpFactory.Draw();
	lpResarch.Draw(TimeTransFlag);
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
}

unique_base Game::UpDate(unique_base own,const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;


	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	Timer(controller);
	lpMapCtl.SetDate(date);
	Draw();

	if (Key[KEY_INPUT_S] & ~KeyOld[KEY_INPUT_S])
	{
	}

	//設置するIDの切り替え
	if (Key[KEY_INPUT_LCONTROL] & (~KeyOld[KEY_INPUT_LCONTROL]))
	{
		id = (Map_ID)(id + 1);
		if (id >= Map_ID::water)
		{
			id = Map_ID::mine;
		}
	}

	//施設の設置
	if (Click&(ClickOld))
	{
		if (lpMapCtl.GetPanelStatus(Mpos + VECTOR2(-100, -50)).BuildFlag == true)
		{
			if (id == Map_ID::field)
			{
				if (lpMapCtl.GetPanelStatus(Mpos + VECTOR2(-90, -50)).WaterFlag == true
					|| lpMapCtl.GetPanelStatus(Mpos + VECTOR2(-110, -50)).WaterFlag == true
					|| lpMapCtl.GetPanelStatus(Mpos + VECTOR2(-100, -60)).WaterFlag == true
					|| lpMapCtl.GetPanelStatus(Mpos + VECTOR2(-100, -40)).WaterFlag == true)
				{
					lpMapCtl.SetMapData(Mpos + VECTOR2(-100, -50), id);
				}
			}
			else
			{
				lpMapCtl.SetMapData(Mpos + VECTOR2(-100, -50), id);
			}
		}
	}

	if (date.minute % 60 == 0)
	{
		lpFactory.UpDate();
		if (WorldName.find(".png") == string::npos)
		{
			SaveDrawScreenToPNG(100, 50, 700, 650, ("img/worldimg/" + WorldName + ".png").c_str());
		}
		else
		{
			SaveDrawScreenToPNG(100, 50, 700, 650, ("img/worldimg/" + WorldName.erase(WorldName.find(".png")) + ".png").c_str());
		}
	}
	if (Key[KEY_INPUT_ESCAPE] & ~KeyOld[KEY_INPUT_ESCAPE])
	{
		lpSceneMng.SetEndFlag(true);
		lpMapCtl.MapSave(false, WorldName);
	}
	return move(own);
}
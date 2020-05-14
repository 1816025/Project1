#include <string>
#include <time.h>
#include "DxLib.h"

#include "BaseScene.h"
#include "SceneMng.h"
#include "Pose.h"

#include "KeyCtl.h"				//どのｷｰが押されたかを知る

#include "ImageMng.h"			//画像の読み込み
#include "SoundMng.h"			//Soundの読み込み、再生

#include "Factory.h"			//資源の生成処理
#include "Laboratory.h"			//研究項目

#include "Noise.h"				//ノイズを生成する
#include "IslandGenerator.h"	//Mapを作成する
#include "MAP_ID.h"
#include "MapCtl.h"				//マップの操作
#include "Event.h"				//イベント

#include "Game.h"				//自分

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
	date = {Season::spring,Weather::Sunny, 1,1,1,0,0 };
	Frame = 0;
	TimeTransFlag = true; //trueでFrame加算
	CntSpeed = 1;
	Debug = false;
	srand(time(NULL));
	auto ImageSize = [=](string name,VECTOR2 divSize,VECTOR2 divCnt)
	{
		GetGraphSize(lpImageMng.GetID("img/" + name + ".png", divSize, divCnt)[1], &this->ImageSize[name].x,&this->ImageSize[name].y);
	};
	ImageSize("icon", VECTOR2(30, 30), VECTOR2(3, 1));
	ImageSize("TAB", VECTOR2(150, 70), VECTOR2(2, 1));
	id = Map_ID::mine;

	lpSoundMng.GetID("sounddata/wave.mp3");
	lpSoundMng.PlaySound("sounddata/wave.mp3", PlayType::Loop);
	lpLabo.GetInstance();
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
		if (Frame > 1)
		{
			date.hour += 1;
			Frame = 0;
			if (date.minute % 60 == 0)
			{
				date.hour += 1;
				date.minute = 0;
				if (date.hour % 24 == 0)
				{
					SetWeather(static_cast<Season>(date.month% static_cast<int>(Season::max)));
					date.day += 1;
					date.hour = 0;
					if (date.day % 30 == 0)
					{
						date.month += 1;
						date.day = 1;
						switch ((date.month / 4) % 4)
						{
						case 0:
							date.season = Season::spring;
							break;
						case 1:
							date.season = Season::summer;
							break;
						case 2:
							date.season = Season::autumn;
							break;
						case 3:
							date.season = Season::winter;
							break;
						default:
							break;
						}
						if (date.month % 12 == 0)
						{
							date.year += 1;
							date.month = 1;
						}
					}
				}
			}
		}
	}

	for (int num = 0; num < 3; num++)
	{
		if (Click&(ClickOld) && Mpos > VECTOR2(300 + ImageSize["icon"].x * num, 0) && Mpos < VECTOR2(300 + ImageSize["icon"].x * num + ImageSize["icon"].x, ImageSize["icon"].y))
		{
			switch (num)
			{
			case 0:
				lpSoundMng.StopSound("sounddata/wave.mp3");
				TimeTransFlag = false;
				break;
			case 1:
				lpSoundMng.StopSound("sounddata/wave.mp3");
				lpSoundMng.PlaySound("sounddata/wave.mp3", PlayType::Loop);
				TimeTransFlag = true;
				CntSpeed = 1;
				break;
			case 2:
				lpSoundMng.StopSound("sounddata/wave.mp3");
				lpSoundMng.PlaySound("sounddata/wave.mp3", PlayType::Loop);
				TimeTransFlag = true;
				CntSpeed = 10;
				break;
			}
		}
	}
	for (int num = 0; num < 2; num++)
	{
		if (Click&(ClickOld) && Mpos > VECTOR2(15 + (15 * num + ImageSize["TAB"].x*num), ScreenSize.y - ImageSize["TAB"].y) && Mpos < VECTOR2(ImageSize["TAB"].x + 15 + (15 * num + ImageSize["TAB"].x*num), ScreenSize.y))
		{
			if (num == 1)
			{
				TimeTransFlag = false;
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

void Game::SetWeather(Season season)
{
	Weather tmp_Weather = Weather::Sunny;
	if (date.cainWeather < 0)
	{
		if (date.weather == Weather::Storm)
		{
			lpFactory.SetStockPile(0,0,0, -((rand() % 5) + 5));
		}
		date.cainWeather = (rand() % 10) + 1;
		tmp_Weather = static_cast<Weather>(rand() % static_cast<int>(Weather::Snow));
		if (season == Season::winter && date.weather == Weather::Rain)
		{
			date.weather = Weather::Snow;
		}
		else
		{
			if (season == Season::summer && date.weather == Weather::Rain)
			{
				if (rand() % 3 == 0)
				{
					date.weather = Weather::Storm;
				}
			}
			if (date.weather != tmp_Weather)
			{
				date.weather = tmp_Weather;
			}
			else
			{
				date.weather = Weather::Cloudy;
			}
		}
	}

	if (date.cainWeather >= 7 || lpEvent.CheckEvent() == true)
	{
		lpEvent.PlayEvent(EVENT::AbnormalWeather,date.weather);
		if (date.cainWeather <= 0)
		{
			lpEvent.SetEvent(false,lpEvent.GetEvent().id);
		}
		date.cainWeather--;
	}
	if (date.cainWeather <= 7 && lpEvent.CheckEvent() == false)
	{
		date.cainWeather--;
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
	DrawFormatString(0, 0, 0xffffff, "%d年目 %2d月%2d日\n%2d時%2d分\n季節%d\n天気%d", date.year, date.month, date.day, date.hour, date.minute,date.season,date.weather);
	for (int y = 0; y <= DisplaySizeY / ChipSize; y++)
	{
		DrawLine(100,  50+(ChipSize*y), 100+ (ChipSize * (DisplaySizeY / ChipSize)), 50+(ChipSize*y), 0x666666);
	}
	for (int x = 0; x <= DisplaySizeX / ChipSize; x++)
	{
		DrawLine(100+(ChipSize*x), 50,100+ (ChipSize*x), 50+(ChipSize*(DisplaySizeX / ChipSize)),  0x666666);
	}
	for(int num = 0; num <3;num++)
	{
		DrawGraph(300 + (ImageSize["icon"].x * num), 0, lpImageMng.GetID("img/icon.png", VECTOR2(30, 30), VECTOR2(3, 1))[num], true);
	};
	for (int num = 0; num < 2; num++)
	{
		DrawGraph(15+(15*num + ImageSize["TAB"].x*num), ScreenSize.y - ImageSize["TAB"].y, lpImageMng.GetID("img/TAB.png", VECTOR2(150, 70), VECTOR2(2, 1))[num], true);
	}


	DrawFormatString(0, 680, 0xffffff, "Mpos.x%d Mpos.y%d",Mpos.x,Mpos.y);
	DrawFormatString(0, 700, 0xffffff, "ID:%d",static_cast<int>(id));
	DrawFormatString(0, 720, 0xffffff, "type: %d",lpMapCtl.GetPanelConter(Map_ID::field));
	DrawFormatString(0, 760, 0xffffff, "Nature: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).BuildFlag);
	lpFactory.Draw();
	if (TimeTransFlag == false)
	{
		if (OptionFlag)
		{
			lpPose.Draw(true);
		}
		else
		{
			lpPose.Draw(false);
		}
	}
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
		date.cainWeather = 10;
		date.weather = Weather::Sunny;
	}

	//設置するIDの切り替え
	if (Key[KEY_INPUT_LCONTROL] & (~KeyOld[KEY_INPUT_LCONTROL]))
	{
		id = (Map_ID)(id + 1);
		if (id >= Map_ID::water2)
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
		lpFactory.UpDate(date);
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
#include <string>
#include <time.h>
#include <Windows.h>

#include "DxLib.h"

#include "BaseScene.h"
#include "SceneMng.h"
#include "Pose.h"

#include "KeyCtl.h"				//どのｷｰが押されたかを知る

#include "ImageMng.h"			//画像の読み込み
#include "SoundMng.h"			//Soundの読み込み、再生
#include "BookList.h"

#include "Noise.h"				//ノイズを生成する
#include "MAP_ID.h"
#include "MapCtl.h"				//マップの操作
#include "Achievement.h"		//実績
#include "Event.h"				//イベント

#include "Game.h"				//自分

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
	TimeTransFlag = true; //trueでFrame加算
	SetObjectFlag = false;
	CntSpeed = 1;
	Pose = false;
	WorldRank = 0;
	srand(time(NULL));
	auto ImageSize = [=](string name,VECTOR2 divSize,VECTOR2 divCnt)
	{
		GetGraphSize(lpImageMng.GetID("img/" + name + ".png", divSize, divCnt)[1], &this->ImageSize[name].x,&this->ImageSize[name].y);
	};
	ImageSize("icon", VECTOR2(30, 30), VECTOR2(3, 1));
	GetGraphSize(lpImageMng.GetID("img/Bookicon.png")[0], &this->ImageSize["Bookicon"].x, &this->ImageSize["Bookicon"].y);
	ImageSize("TAB", VECTOR2(150, 70), VECTOR2(2, 1));
	id = Map_ID::BOOK_SHELF;
	lpMapCtl.SetUp(VECTOR2(400, 400), VECTOR2(16, 16), VECTOR2(300, 100));
	lpSoundMng.GetID("sounddata/Library.mp3");
	lpSoundMng.ChangeVol(25, "sounddata/Library.mp3");
	lpSoundMng.PlaySound("sounddata/Library.mp3", PlayType::Loop);
	fontHandle["font01"] = CreateFontToHandle("font01", 24, 9, DX_FONTTYPE_EDGE,-1,2);
	fontHandle["font02"] = CreateFontToHandle("font02", 35, 9, DX_FONTTYPE_EDGE,-1,2,2);
	lpBookList.SetLibraryScore();
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
	Frame++;

	date.daycycle = static_cast<DayCycle>(date.hour / 24 % static_cast<int>(DayCycle::Max));
	if (Frame%(20) == 0)
	{
		date.minute += 1;
		if (date.minute % (20) == 0)
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
			if (date.hour > 24)
			{
				date.day += 1;
				date.hour = 0;
				for (int index = 0; index < lpAchievement.GetAchievement().size(); index++)
				{
					lpAchievement.UpDate(lpAchievement.GetAchievement()[index], { false,date,lpBookList.GetLibraryScore(),lpBookList.GetBookCnt(),CollectCnt });
				}
				OpenFlag = (date.day % 4 != 0 ? true : false);
				lpBookList.SetLibraryScore();
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
	auto Click = controller.GetClick(NOW);
	auto ClickOld = controller.GetClick(OLD);


	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	if (lpEvent.GetEvent().flag == false)
	{
		Timer(controller);
	}
	lpMapCtl.SetDate(date);

	//設置するIDの切り替え
	if (Key[KEY_INPUT_LCONTROL] & (~KeyOld[KEY_INPUT_LCONTROL]))
	{
		id = (Map_ID)(id + 1);
		if (id > Map_ID::DESK)
		{
			id = Map_ID::BOOK_SHELF;
		}
	}

	//施設の設置

	for (int num = 0; num < 2; num++)
	{
		if (Click&(~ClickOld) && Mpos > VECTOR2(15 + (15 * num + ImageSize["TAB"].x*num), ScreenSize.y - ImageSize["TAB"].y) && Mpos < VECTOR2(ImageSize["TAB"].x + 15 + (15 * num + ImageSize["TAB"].x*num), ScreenSize.y))
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

	if (Click&(~ClickOld) && Mpos > VECTOR2(10, 450) && Mpos < VECTOR2(10 + ImageSize["Bookicon"].x, 450 + ImageSize["Bookicon"].y))
	{
		if (Pose == false)
		{
			Pose = true;
		}
		else
		{
			Pose = false;
		}
	}

	if (Key[KEY_INPUT_ESCAPE] & ~KeyOld[KEY_INPUT_ESCAPE])
	{
		lpMapCtl.MapSave(false, WorldName);
		lpBookList.DataSave("BookArchive");
		lpSoundMng.StopSound("sounddata/Library.mp3");
		lpSceneMng.SetEndFlag(true);
	}
/*
	if (Key[KEY_INPUT_A] & ~KeyOld[KEY_INPUT_A])
	{
		lpBookList.SetLibraryScore();
	}

	if (Key[KEY_INPUT_D] & ~KeyOld[KEY_INPUT_D])
	{
		date.daycycle = DayCycle::Night;
		lpEvent.PlayEvent(EVENT::Raid);
	}

	if (Key[KEY_INPUT_S] & ~KeyOld[KEY_INPUT_S])
	{
		lpEvent.PlayEvent(EVENT::Donation);
	}
*/
	//if (OpenFlag == true)
	//{
	//	///*開館時のイベント(昼)*/
	//	//if (date.daycycle == DayCycle::Day)
	//	//{
	//	//	if (lpEvent.CheckEvent())
	//	//	{
	//	//		TimeTransFlag = false;
	//	//	}

	//	//	if (Key[KEY_INPUT_S] & ~KeyOld[KEY_INPUT_S])
	//	//	{
	//	//		lpEvent.PlayEvent(EVENT::Donation);
	//	//	}

	//	//	if (Key[KEY_INPUT_W] & ~KeyOld[KEY_INPUT_W])
	//	//	{
	//	//		lpEvent.PlayEvent(EVENT::Debut);
	//	//	}

	//	//	if (lpEvent.GetEvent().id == EVENT::Raid && lpEvent.GetEvent().flag == true)
	//	//	{
	//	//		lpEvent.SetEvent(false, EVENT::Raid);
	//	//	}
	//	//} 
	//	//else
	//	//{
	//	//	lpEvent.PlayEvent(EVENT::Raid);
	//	//}
	//}
	//else
	//{
	//	if (date.daycycle == DayCycle::Day)
	//	{
	//		if (Click&(~ClickOld) )
	//		{
	//			if (lpMapCtl.GetMapData(Mpos + VECTOR2(-OffSetX, -OffSetY)) == Map_ID::NON || id == Map_ID::NON)
	//			{
	//				lpMapCtl.SetMapData(Mpos + VECTOR2(-OffSetX, -OffSetY), id);
	//			}
	//		}
	//	}
	//}

	if (SetObjectFlag)
	{
		if (Click&(~ClickOld))
		{
			if (lpMapCtl.GetMapData(Mpos + VECTOR2(-OffSetX, -OffSetY)) == Map_ID::NON || id == Map_ID::NON)
			{
				lpMapCtl.SetMapData(Mpos + VECTOR2(-OffSetX, -OffSetY), id);
			}
		}
	}

	if (lpEvent.CheckEvent() == true)
	{
		lpEvent.UpDate(controller);
	}
	if (lpEvent.CheckEvent() == false && date.hour % 12 == 8 && date.minute == 0)
	{
		Phase(date.daycycle);
	}
	if (date.minute%60 == 0)
	{
		if (WorldName.find(".png") == string::npos)
		{
			SaveDrawScreenToPNG(OffSetX, OffSetY, 300 + 400, 100 + 400, ("img/worldimg/" + WorldName + ".png").c_str());
		}
		else
		{
			SaveDrawScreenToPNG(OffSetX, OffSetY, OffSetX - 16 + 432, OffSetX - 16 + 448, ("img/" + WorldName.erase(WorldName.find(".png")) + ".png").c_str());
		}
	}
	Draw();
	return move(own);
}

void Game::Draw()
{
	auto Mpos = VECTOR2(0, 0);
	GetMousePoint(&Mpos.x, &Mpos.y);
	// 画面を初期化(真っ黒にする)
	ClearDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("img/books.png")[0], false);

	if (lpEvent.CheckEvent() == true && lpEvent.GetEvent().id == EVENT::Donation)
	{
		lpEvent.Draw();
	}
	else
	{
		DrawGraph(OffSetX - 16, OffSetY - 32, lpImageMng.GetID("img/wall.png")[0], true);
		lpMapCtl.Draw();
		for (int y = 0; y <= DisplaySizeY / ChipSize; y++)
		{
			DrawLine(OffSetX, OffSetY + (ChipSize*y), OffSetX + (ChipSize * (DisplaySizeY / ChipSize)), OffSetY + (ChipSize*y), 0x8b8781);
		}
		for (int x = 0; x <= DisplaySizeX / ChipSize; x++)
		{
			DrawLine(OffSetX + (ChipSize*x), OffSetY, OffSetX + (ChipSize*x), OffSetY + (ChipSize*(DisplaySizeX / ChipSize)), 0x8b8781);
		}
		//DrawGraph(OffSetX, OffSetY, lpImageMng.GetID( "img/Redhood.png",VECTOR2(16, 16), VECTOR2(3, 4))[1], true);
	}
	if (Pose)
	{
		DrawGraph(0, 0, lpImageMng.GetID("img/books.png")[0], false);
		DrawBox(ScreenSize.x / 2 - 50, 75, ScreenSize.x - 100, ScreenSize.y -100, 0x00, true);
		DrawBox(100, ScreenSize.y -300,300, ScreenSize.y - 100, 0x00, true);
		DrawFormatString(125, 320, 0xffffff, "BookCnt: %d冊", lpBookList.GetBookCnt());
		DrawFormatString(125, 360, 0xffffff, "LibraryRank: ");
		DrawFormatStringToHandle(490, 30, 0x00ffff, fontHandle["font02"], "実績");

		if (lpBookList.GetLibraryScore() < 10000)
		{
			DrawFormatStringToHandle(260, 350, 0xffffff, fontHandle["font01"], "D");
		}
		else if (lpBookList.GetLibraryScore() < 50000)
		{
			DrawFormatStringToHandle(260, 350, 0xfffff8, fontHandle["font01"], "C");
		}
		else if (lpBookList.GetLibraryScore() < 500000)
		{
			DrawFormatStringToHandle(260, 350, 0xfffff0, fontHandle["font01"], "B");
		}
		else if (lpBookList.GetLibraryScore() < 1000000)
		{
			DrawFormatStringToHandle(260, 350, 0xffff8f, fontHandle["font01"], "A");
		}
		else if (lpBookList.GetLibraryScore() < 5000000)
		{
			DrawFormatStringToHandle(260, 350, 0xffff80, fontHandle["font01"], "S");
		}
		else if (lpBookList.GetLibraryScore() < 10000000)
		{
			DrawFormatStringToHandle(260, 350, 0xffff00, fontHandle["font01"], "SS");
		}
		for (int num = 0;num< lpAchievement.GetAchievement().size(); num++)
		{
			DrawFormatString(400, 100 + 20*num, 0xffffff,lpAchievement.GetAchievement()[num].c_str());
			DrawFormatString(600, 100 + 20*num, 0xffffff, (lpAchievement.GetAchievementData(lpAchievement.GetAchievement()[num]).flag == true ? "達成済み" : "未達成"));
		}
	}
	DrawFormatStringToHandle(0, 0, 0xffffff, fontHandle["font01"], "%d年目 %2d月%2d日\n%2d時%2d分", date.year, date.month, date.day, date.hour, date.minute);
	
	DrawFormatString(0, 680, 0xffffff, "Mpos.x%d Mpos.y%d", Mpos.x, Mpos.y);
	DrawFormatString(0, 760, 0xffffff, "Nature: %d", lpMapCtl.GetPanelStatus(VECTOR2(Mpos.x - 100, Mpos.y - 50)).BuildFlag);
	DrawGraph(10, 450, lpImageMng.GetID("img/Bookicon.png")[0], true);
	// 裏画面の内容を表画面にコピーする（描画の確定）.
	ScreenFlip();
}

void Game::Phase(DayCycle cycle)
{
	switch (cycle)
	{
	case DayCycle::Day:
		if (OpenFlag == true)
		{
			SetObjectFlag = false;
		}
		else
		{
			SetObjectFlag = true;
		}
		if (rand() % 60 == 0)
		{
			CollectCnt++;
			lpEvent.PlayEvent(EVENT::Donation);
		}
		if (rand() % 90 == 0)
		{
			lpEvent.PlayEvent(EVENT::Debut);
		}
		break;
	case DayCycle::Night:
		if (rand() % 40 == 0)
		{

		}
		if (rand() % 60 == 0)
		{
			lpEvent.PlayEvent(EVENT::Favorability);
			//友好度上昇イベント
		}
		break;
	default:
		break;
	}
}

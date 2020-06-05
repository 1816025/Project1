#include "DxLib.h"
#include "VECTOR2.h"
#include "BaseScene.h"
#include "KeyCtl.h"
#include "MAP_ID.h"
#include "MapCtl.h"
#include "Game.h"
#include "ImageMng.h"
#include "Unit.h"
#include "Favorability.h"
#include "Raid.h"
#include "BookList.h"
#include "Event.h"

Event::Event()
{
	GetGraphSize(lpImageMng.GetID("img/bookicon.png")[0], &ImageSize["icon"].x, &ImageSize["icon"].y);
}

Event::~Event()
{
}

void Event::UpDate(const KeyCtl &controller)
{
	auto Key = controller.GetCtl(NOW);
	auto KeyOld = controller.GetCtl(OLD);
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;
	VECTOR2 Mpos = { 0,0 };
	GetMousePoint(&Mpos.x, &Mpos.y);
	switch (data.id)
	{
	case EVENT::Donation:
		for (int num = 0; num < Candidate.size(); num++)
		{
			if (Click&(ClickOld)
				&& Mpos > VECTOR2(OffSetX / 1.5 + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2)
				&& Mpos < VECTOR2((OffSetX / 1.5) + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2) + ImageSize["icon"])
			{
				SetEvent(false, EVENT::Donation);
				//Œ»ÝŠ—L‚µ‚Ä‚¢‚È‚¯‚ê‚ÎŠl“¾‚Å‚«‚é
				if (lpBookList.GetLibrary()[lpBookList.GetLibraryIndex(Candidate[num])] == false)
				{
					lpBookList.SetLibrary(lpBookList.GetLibraryIndex(Candidate[num]), true);
				}
				lpBookList.SetBookCnt(10);
			}
		}
		break;
	case EVENT::Debut:
		SetEvent(false, EVENT::Debut);
		lpBookList.ChangeStatus(lpBookList.GetAuthor()[rand() % lpBookList.GetAuthor().size()]);
		break;
	case EVENT::Raid:
		lpRaid.UpDate();
	case EVENT::Favorability:
		SetEvent(false, EVENT::Favorability);
		if (!(lpBookList.GetFavorabilityList(true).empty()))
		{
			lpFavorability.UpDate(rand() % lpBookList.GetFavorabilityList(true).size(), controller);
		}
		break;
	default:
		break;
	}
}

void Event::Draw(void)
{
	if (GetEvent().id == EVENT::Donation)
	{
		for (int num = 0; num < Candidate.size(); num++)
		{
			DrawGraph(OffSetX / 1.5 + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2, lpImageMng.GetID("img/bookicon.png")[0], true);
			DrawFormatString(OffSetX / 2 + (OffSetX / 1.5)*num, ScreenSize.y / 2 - OffSetY / 1.5, 0xffffff, "%s", Candidate[num].c_str());
		}
		//DrawFormatString(0, 0, 0xffffff, "%d\n%d\n%d", Candidate[0], Candidate[1], Candidate[2]);
	}
	if (GetEvent().id == EVENT::Favorability)
	{
		for (int num = 0; num < static_cast<int>(MISSION::MAX); num++)
		{
			DrawGraph(OffSetX / 1.5 + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2, lpImageMng.GetID("img/bookicon.png")[0], true);
		}
	}
}

void Event::PlayEvent(EVENT eventtype)
{
	SetEvent(true, eventtype);

	if (eventtype == EVENT::Donation)
	{
		for (int num = 0; num < 3; num++)
		{
			auto tmpf = lpBookList.GetArchive(rand() % lpBookList.GetArchiveSize());
			if (std::find(Candidate.begin(), Candidate.end(), tmpf)== Candidate.end())
			{
				Candidate[num] = tmpf;
			}
			else
			{
				num--;
				continue;
			}
		}
	}
}

const bool Event::CheckEvent()
{
	return data.flag;
}

void Event::SetEvent(bool flag, EVENT eventtype)
{
	data.flag = flag;
	data.id = eventtype;
}

const EventData Event::GetEvent()
{
	return data;
}

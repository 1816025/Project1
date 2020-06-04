#include <string>
#include "DxLib.h"
#include "BaseScene.h"
#include "ImageMng.h"
#include "BookList.h"
#include "KeyCtl.h"
#include "VECTOR2.h"
#include "Favorability.h"

Favorability::Favorability()
{
	ImageSize["icon"] = lpImageMng.GetImageSize("img/bookicon.png");
	PresentStatus = { 10,25 };
}

Favorability::~Favorability()
{
}

void Favorability::UpDate(int index, const KeyCtl &controller)
{
	auto Click = (GetMouseInput()&MOUSE_INPUT_LEFT);
	auto ClickOld = Click;
	auto Mpos = VECTOR2(0, 0);
	auto mission = MISSION::MAX;
	if (lpBookList.GetFriendshipValue(index) != 100)
	{
		for (int num = 0; num < static_cast<int>(MISSION::MAX); num++)
		{
			if (Click&ClickOld
				&& Mpos > VECTOR2(OffSetX / 1.5 + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2)
				&& Mpos < VECTOR2((OffSetX / 1.5) + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2) + ImageSize["icon"])
			{
				mission = static_cast<MISSION>(num);
			}
		}
		switch (mission)
		{
		case MISSION::Talk:
			lpBookList.SetFriendshipValue(index, 10);
			break;
		case MISSION::Present:

			if (Click&(~ClickOld))
			{
				for (int num = 0; num < static_cast<int>(PresentData::MAX); num++)
				{
					if (Click&ClickOld
						&& Mpos > VECTOR2(OffSetX / 1.5 + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2)
						&& Mpos < VECTOR2((OffSetX / 1.5) + (OffSetX / 1.5)*num, ScreenSize.y / 2 + OffSetY / 2) + ImageSize["icon"])
					{
						lpBookList.SetFriendshipValue(index,PresentStatus[num]);
					}
				}
			}
			lpBookList.SetFriendshipValue(index, 10);
			break;
		case MISSION::MAX:
			break;
		default:
			break;
		}
	}
}


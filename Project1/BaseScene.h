#pragma once
#include <DxLib.h>
#include <memory>

#define ScreenSize VECTOR2(800,599)
#define DisplaySizeX 400
#define DisplaySizeY 400
#define ChipSize 16
#define OffSetX 300
#define OffSetY 100

class BaseScene;
class KeyCtl;

using unique_base = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_base UpDate(unique_base own, const KeyCtl &controller) = 0;
};


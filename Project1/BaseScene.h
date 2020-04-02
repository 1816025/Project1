#pragma once
#include <DxLib.h>
#include <memory>

#define DisplaySizeX 600
#define DisplaySizeY 600
#define ChipSize 10
#define OffSetX 100
#define OffSetY 50

class BaseScene;
class KeyCtl;

using unique_base = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_base UpDate(unique_base own, const KeyCtl &controller) = 0;
};


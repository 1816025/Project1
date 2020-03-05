#pragma once
#include <DxLib.h>
#include <memory>

class BaseScene;
class KeyCtl;

using unique_base = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_base UpDate(unique_base own, const KeyCtl &controller) = 0;
};


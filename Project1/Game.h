#pragma once
#include "BaseScene.h"
#include "KeyCtl.h"
class Game:
	public BaseScene
{
public:
	Game();
	~Game();
	unique_base UpDate(unique_base own,const KeyCtl &controller);
private:
	int Init();
	void Draw();
	bool TimeTransFlag;
	int Frame;
};


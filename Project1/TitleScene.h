#pragma once
#include "BaseScene.h"
#include "VECTOR2.h"

struct SelectMode
{
	VECTOR2 NewWorld;
	VECTOR2 Continue;
};

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_base UpDate(unique_base own, const KeyCtl &controller);
private:
	void Init();
	void TitleDraw(void);
	SelectMode start;
	VECTOR2 titleSize;
};


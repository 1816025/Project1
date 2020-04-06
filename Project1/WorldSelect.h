#pragma once
#include <string>
#include "BaseScene.h"
using namespace std;
class WorldSelect :
	public BaseScene
{
public:
	WorldSelect();
	~WorldSelect();
	unique_base UpDate(unique_base own, const KeyCtl &controller);
private:
	string WorldChoice();
	void Draw();

	string worldName;
};


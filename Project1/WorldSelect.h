#pragma once
#include <vector>
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
	string WorldChoice(const VECTOR2& Mpos, const KeyCtl & controller);
	void Draw();

	string WorldName;
	int WorldId;
	VECTOR2 drawOffset;
	VECTOR2 Mpos;
	vector<string>WorldData;

	FILEINFO FileInfo;
	DWORD_PTR FindHandle;
};


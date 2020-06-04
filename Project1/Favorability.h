#pragma once
#include <map>
#include <array>
#define lpFavorability Favorability::GetInstance()
using namespace std;
enum class MISSION
{
	Talk,
	Present,
	MAX
};

enum class PresentData
{
	BookMark,
	Cake,
	MAX
};
class Favorability
{
public:
	static Favorability& GetInstance()
	{
		static Favorability s_Instance;
		return s_Instance;
	}
	void UpDate(int index, const KeyCtl &controller);

private:
	Favorability();
	~Favorability();
	map<string, VECTOR2>ImageSize;
	array<int, static_cast<int>(PresentData::MAX)>PresentStatus;
};


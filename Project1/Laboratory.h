#pragma once
#include <vector>

enum class ResearchList
{
	//農業関連
	Farmland,				//農地ができるようになる
	Livestock,				//牧畜ができるようになる
	Irrigation,				//水路が引けるようになる
	Greenhouse,				//冬の生産量を増やす
	Plantation,				//大規模農業
	Breed_improvement,		//品種改良
	//林業関連
	Felling,				//伐採場が建てられるようになる
	Sawmill,				//木材加工ができるようになる
	Shipbuilding,			//造船ができるようになる
	//工業・軍事関連
	Mining,					//採鉱が出来るようになる
	Bronze,					//青銅器が作れるようになる
	Ironware,				//鉄器が作れるようになる
	Steam,					//蒸気機関が開始できる
	Saltpeter,				//硝石が採取出来る・火器爆発物が作れるようになる
	//娯楽公共施設
	Wooden_construction,	//木造建築解放
	Disaster_prevention,	//防災
	MAX
};

#define lpLabo Laboratory::GetInstance()

using namespace std;/*
using Research_int  = vector<ResearchList, int>;
using Research_enum = vector<ResearchList, static_cast<size_t>(ResearchList::MAX)>;*/

class Laboratory
{
public:
	static Laboratory &GetInstance(void)
	{
		static Laboratory s_Instance;
		return s_Instance;
	}
	void UpDate();
	void Draw();
private:
	Laboratory();
	~Laboratory();

	//vector<bool,ResearchList> ResarchFlag;		//研究できるかどうか
	//Research_int  ResarchTime;
	//Research_enum ResaechNext;
};


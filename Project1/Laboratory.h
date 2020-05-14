#pragma once
#include <vector>

enum class ResearchList
{
	//�_�Ɗ֘A
	Farmland,				//�_�n���ł���悤�ɂȂ�
	Livestock,				//�q�{���ł���悤�ɂȂ�
	Irrigation,				//���H��������悤�ɂȂ�
	Greenhouse,				//�~�̐��Y�ʂ𑝂₷
	Plantation,				//��K�͔_��
	Breed_improvement,		//�i�����
	//�ыƊ֘A
	Felling,				//���̏ꂪ���Ă���悤�ɂȂ�
	Sawmill,				//�؍މ��H���ł���悤�ɂȂ�
	Shipbuilding,			//���D���ł���悤�ɂȂ�
	//�H�ƁE�R���֘A
	Mining,					//�̍z���o����悤�ɂȂ�
	Bronze,					//���킪����悤�ɂȂ�
	Ironware,				//�S�킪����悤�ɂȂ�
	Steam,					//���C�@�ւ��J�n�ł���
	Saltpeter,				//�ɐ΂��̎�o����E�Ί픚����������悤�ɂȂ�
	//��y�����{��
	Wooden_construction,	//�ؑ����z���
	Disaster_prevention,	//�h��
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

	//vector<bool,ResearchList> ResarchFlag;		//�����ł��邩�ǂ���
	//Research_int  ResarchTime;
	//Research_enum ResaechNext;
};


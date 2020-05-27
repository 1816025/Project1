#pragma once
#include <vector>
#include "VECTOR2.h"

#define lpUnit Unit::GetInstance()
enum class GroupStatus
{
	ALLY,		//����
	ACTIVE,		//�G�ΐ���(�G�Ώ��)
	NON,
	MAX
};

enum class GroupName
{
	HUMAN,
	BEAR,
	SNAKE,
	WOLF,
	MAX
};

struct GroupParameter
{
	GroupStatus Status;		//�G�����̎���
	int Lp;					//�̗�
	int Ap;					//�U����
	int As;					//�U�����x
	VECTOR2 pos;			//���W
};
using namespace std;
class Unit
{
public:
	static Unit& GetInstance()
	{
		static Unit s_Instance;
		return s_Instance;
	}
	void UpDate(void);
	void SetPos(VECTOR2 pos, int index);
	VECTOR2 GetPos(int index);
	const vector<GroupParameter> GetUnitList();	
	const GroupParameter GetUnitList(int index);

	const int GetUnitStatus(VECTOR2 pos);	//���̍��W�ɑ��݂��郆�j�b�g���ǂ̂悤�ȑ��݂���Ԃ�

	void BattlePhase(int index, int enemy_index);		//���j�b�g���o��ƌĂ΂��
	void EndPhase(int index, int enemy_index);			//���s�����܂�ƌĂ΂��
	void PopPhase(GroupParameter param);			    //���s�����܂�ƌĂ΂��

private:
	Unit();
	~Unit();

	vector<GroupParameter> UnitList;	//�G�������������Ă���
};


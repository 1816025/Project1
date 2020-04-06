#pragma once
#include <array>

enum KEY_TYPE			//����1�O�̷����
{
	NOW,
	OLD,
	MAX,
};

struct type
{
	int now;
	int old;
};

using KeyArray = std::array<char, 256>;

class KeyCtl
{
public:
	bool UpDate(void);
	const KeyArray& GetCtl(KEY_TYPE type)const;
	const bool GetClick(int mousetype, KEY_TYPE type);
	const bool CheckWheel(KEY_TYPE type);
private:
	KeyArray data;
	KeyArray dataOld;
	type Click;
	type wheel;
};


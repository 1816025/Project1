#pragma once
#include <array>

enum KEY_TYPE			//����1�O�̷����
{
	NOW,
	OLD,
	MAX,
};
using KeyArray = std::array<char, 256>;

class KeyCtl
{
public:
	bool UpDate(void);
	const KeyArray& GetCtl(KEY_TYPE type)const;
private:
	KeyArray data;
	KeyArray dataOld;
};


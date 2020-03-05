#pragma once
#include <array>

enum KEY_TYPE			//¡‚Æ1‚Â‘O‚Ì·°î•ñ
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


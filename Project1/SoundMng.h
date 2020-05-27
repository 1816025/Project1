#pragma once
#include <map>
#include <vector>

#ifdef _DEBUG
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %ds–Ú0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "±»°Ä•\¦", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG

#define lpSoundMng SoundMng::GetInstance()
#define IMAGE_ID(X) (SoundMng::GetInstance().GetID(X))

using namespace std;
using VEC_INT = vector<int>;

enum class PlayType
{
	Normal,
	Back,
	Loop,
	Max
};

class SoundMng
{
public:
	static SoundMng &GetInstance(void)
	{
		static SoundMng s_Instance;
		return s_Instance;
	}
	const VEC_INT& GetID(std::string f_name);		// SEÊİÄŞÙ‚Ì“üè
	const int& PlaySound(string f_name,PlayType type);
	const int& StopSound(string f_name);
	const int& ChangeVol(int vol,string f_name);

private:
	map<string, VEC_INT> SoundData;
};


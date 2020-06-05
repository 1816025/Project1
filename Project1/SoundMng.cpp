#include "DxLib.h"
#include "SoundMng.h"

const VEC_INT & SoundMng::GetID(std::string f_name)
{
	// map‚É±¸¾½‚µ‚½uŠÔÃŞ°À‚ª‚È‚©‚Á‚½‚çƒƒ‚ƒŠ‚ğŠm•Û‚µ‚Ä‚»‚Ì’l‚ğ•Ô‚·
	if (SoundData.find(f_name) == SoundData.end())
	{
		SoundData[f_name].resize(1);
		SoundData[f_name][0] = LoadSoundMem((/*"image/" + */f_name/* + ".png"*/).c_str());
		if (SoundData[f_name][0] == -1)
		{
			AST();
		}
	}
	return SoundData[f_name];
}

const int & SoundMng::PlaySound(string f_name, PlayType type)
{
	switch (type)
	{
	case PlayType::Normal:
		return PlaySoundMem(SoundData[f_name][0], DX_PLAYTYPE_NORMAL);
		break;
	case PlayType::Back:
		return PlaySoundMem(SoundData[f_name][0], DX_PLAYTYPE_BACK);
		break;
	case PlayType::Loop:
		return PlaySoundMem(SoundData[f_name][0], DX_PLAYTYPE_LOOP);
		break;
	case PlayType::Max:
		break;
	default:
		break;
	}
}

const int & SoundMng::StopSound(string f_name)
{
	if (CheckSoundMem(SoundData[f_name][0]) == 1)
	{
		return StopSoundMem(SoundData[f_name][0]);
	}
}

const int & SoundMng::ChangeVol(int vol,string f_name)
{
	return ChangeVolumeSoundMem(255*vol/100,SoundData[f_name][0]);
}

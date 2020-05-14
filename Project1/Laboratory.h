#pragma once
#include <vector>

enum class ResearchList
{
	//”_‹ÆŠÖ˜A
	Farmland,				//”_’n‚ª‚Å‚«‚é‚æ‚¤‚É‚È‚é
	Livestock,				//–q’{‚ª‚Å‚«‚é‚æ‚¤‚É‚È‚é
	Irrigation,				//…˜H‚ªˆø‚¯‚é‚æ‚¤‚É‚È‚é
	Greenhouse,				//“~‚Ì¶Y—Ê‚ğ‘‚â‚·
	Plantation,				//‘å‹K–Í”_‹Æ
	Breed_improvement,		//•ií‰ü—Ç
	//—Ñ‹ÆŠÖ˜A
	Felling,				//”°Ìê‚ªŒš‚Ä‚ç‚ê‚é‚æ‚¤‚É‚È‚é
	Sawmill,				//–ØŞ‰ÁH‚ª‚Å‚«‚é‚æ‚¤‚É‚È‚é
	Shipbuilding,			//‘¢‘D‚ª‚Å‚«‚é‚æ‚¤‚É‚È‚é
	//H‹ÆEŒR–ŠÖ˜A
	Mining,					//Ìz‚ªo—ˆ‚é‚æ‚¤‚É‚È‚é
	Bronze,					//Â“ºŠí‚ªì‚ê‚é‚æ‚¤‚É‚È‚é
	Ironware,				//“SŠí‚ªì‚ê‚é‚æ‚¤‚É‚È‚é
	Steam,					//ö‹C‹@ŠÖ‚ªŠJn‚Å‚«‚é
	Saltpeter,				//ÉÎ‚ªÌæo—ˆ‚éE‰ÎŠí”š”­•¨‚ªì‚ê‚é‚æ‚¤‚É‚È‚é
	//ŒâŠyŒö‹¤{İ
	Wooden_construction,	//–Ø‘¢Œš’z‰ğ•ú
	Disaster_prevention,	//–hĞ
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

	//vector<bool,ResearchList> ResarchFlag;		//Œ¤‹†‚Å‚«‚é‚©‚Ç‚¤‚©
	//Research_int  ResarchTime;
	//Research_enum ResaechNext;
};


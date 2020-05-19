#pragma once
#include <array>
#include <map>
#include "VECTOR2.h"
#include "KeyCtl.h"
enum class EVENT
{
	Donation,
	Debut,
	Max
};

struct EventData
{
	EVENT id;
	bool flag;
};
#define lpEvent Event::GetInstance()

using namespace std;
class Event
{
public:
	static Event& GetInstance()
	{
		static Event s_Incetance;
		return s_Incetance;
	}
	void UpDate(const KeyCtl &controller);
	void Draw(void);
	void PlayEvent(EVENT eventtype);
	const bool CheckEvent();
	void SetEvent(bool flag,EVENT eventtype);
	const EventData GetEvent(void);
private:
	Event();
	~Event();
	EventData data;
	array<string, 3>Candidate;		//3‚Â‚Ì‘I‘ðŽˆ
	map<string, VECTOR2> ImageSize;
};


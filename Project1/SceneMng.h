#pragma once
#include "BaseScene.h"
#include "KeyCtl.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);
	void SetEndFlag(bool flag);
	bool endflag;
private:
	SceneMng();
	~SceneMng();
	std::unique_ptr<KeyCtl>keyCtl;
	unique_base activeScene;
	bool SysInit();
};


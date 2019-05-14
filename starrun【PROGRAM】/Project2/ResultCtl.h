#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

class ResultCtl
{
public:
	static ResultCtl &GetInstance(void)
	{
		static ResultCtl s_Instance;
		return s_Instance;
	}
	ResultCtl();
	~ResultCtl();
	bool SetUp(const int score, const int time);
	bool ResultSave(sharedListObj objList);					//怴偟偔惂嶌偟偨席踢忣曬偺景剔媦傃SUM联
	bool ResultLoad(sharedListObj objList, bool objFlag);		//曐懚偝傟偨席踢忣曬偺撉傒崬傒媦傃SUM联
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);

private:
	int score;
	int time;
};


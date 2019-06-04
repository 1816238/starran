#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

struct DataHeader
{
	char fileID[12];		//抬操偺ID忣曬
	char verID;			//兽凹蕻軮D
	char reserve1[3];	//梊栺椞堟
	int score;
	int time;
	char reserve2[3];	//梊栺椞堟
	char sum;
};

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
	void SetLoadData(int score, int time);
	const int GetLoadScoreData();
	const int GetLoadScore();		//曐懚偝傟偨score傪屇傃弌偡
	const int GetLoadTimeData();
	const int GetLoadTime();		//曐懚偝傟偨time傪屇傃弌偡
private:
	int score;
	int time;
	int score2;
	int time2;
};

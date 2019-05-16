#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

struct DataHeader
{
	char fileID[12];		//Ì§²Ù‚ÌIDî•ñ
	char verID;			//ÊŞ°¼Ş®İID
	char reserve1[3];	//—\–ñ—Ìˆæ
	int score;
	int time;
	char reserve2[3];	//—\–ñ—Ìˆæ
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
	bool ResultSave(sharedListObj objList);					//V‚µ‚­§ì‚µ‚½Ï¯Ìßî•ñ‚Ì¾°ÌŞ‹y‚ÑSUMÁª¯¸
	bool ResultLoad(sharedListObj objList, bool objFlag);		//•Û‘¶‚³‚ê‚½Ï¯Ìßî•ñ‚Ì“Ç‚İ‚İ‹y‚ÑSUMÁª¯¸
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	void SetLoadData(int score, int time);
	const int GetLoadScoreData();
	const int GetLoadTimeData();
private:
	int score;
	int time;
	int score2;
	int time2;
};

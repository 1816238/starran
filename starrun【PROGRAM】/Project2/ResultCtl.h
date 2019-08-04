#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

struct DataHeader
{
	char fileID[12];		//ﾌｧｲﾙのID情報
	char verID;			//ﾊﾞｰｼﾞｮﾝID
	char reserve1[3];	//予約領域
	int score;
	int time;
	char reserve2[3];	//予約領域
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
	bool ResultSave(sharedListObj objList,string f_name, int score);					//新しく制作したﾏｯﾌﾟ情報のｾｰﾌﾞ及びSUMﾁｪｯｸ
	bool ResultLoad(sharedListObj objList, string f_name, bool objFlag);		//保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	void RankingScore(sharedListObj objList);
	const int GetLoadScore();		//保存されたscoreを呼び出す
	const int GetLoadScore(int num);		//保存されたランキングscoreを呼び出す
	const int GetLoadTime();		//保存されたtimeを呼び出す
	const int GetLoadTime(int num);		//保存されたランキングtimeを呼び出す
private:
	int score;
	int time;
	int rankscore[3];
	int ranktime[3];
};

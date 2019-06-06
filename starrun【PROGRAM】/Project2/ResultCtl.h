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
	bool ResultSave(sharedListObj objList);					//新しく制作したﾏｯﾌﾟ情報のｾｰﾌﾞ及びSUMﾁｪｯｸ
	bool ResultLoad(sharedListObj objList, bool objFlag);		//保存されたﾏｯﾌﾟ情報の読み込み及びSUMﾁｪｯｸ
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	const int GetLoadScore();		//保存されたscoreを呼び出す
	const int GetLoadTime();		//保存されたtimeを呼び出す
private:
	int score;
	int time;
	int score2;
	int time2;
};

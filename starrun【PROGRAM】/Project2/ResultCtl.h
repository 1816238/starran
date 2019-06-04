#pragma once
#include "classObj.h"

#define lpResultCtl ResultCtl::GetInstance()

class Obj;

struct DataHeader
{
	char fileID[12];		//̧�ق�ID���
	char verID;			//�ް�ޮ�ID
	char reserve1[3];	//�\��̈�
	int score;
	int time;
	char reserve2[3];	//�\��̈�
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
	bool ResultSave(sharedListObj objList);					//�V�������삵��ϯ�ߏ��̾��ދy��SUM����
	bool ResultLoad(sharedListObj objList, bool objFlag);		//�ۑ����ꂽϯ�ߏ��̓ǂݍ��݋y��SUM����
	bool SetUpGameObj(sharedListObj objList, bool DrawFlag);
	void SetLoadData(int score, int time);
	const int GetLoadScoreData();
	const int GetLoadScore();		//�ۑ����ꂽscore���Ăяo��
	const int GetLoadTimeData();
	const int GetLoadTime();		//�ۑ����ꂽtime���Ăяo��
private:
	int score;
	int time;
	int score2;
	int time2;
};
